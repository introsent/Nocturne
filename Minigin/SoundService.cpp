#include "SoundService.h"
#include <SDL_mixer.h>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <unordered_map>

#include "Command.h"
#include "LoadSoundCommand.h"
#include "PlaySoundCommand.h"

namespace dae
{
    class SoundService::MixerImpl {
        std::mutex m_queueMutex;
        std::condition_variable m_queueCV;
        std::queue<std::unique_ptr<Command>> m_commandQueue;
        std::jthread m_workerThread;
        std::unordered_map<std::string, Mix_Chunk*> m_sounds;
        bool m_running = true;

        void WorkerLoop() {
            while (m_running) {
                std::unique_lock lock(m_queueMutex);
                m_queueCV.wait(lock, [this] {
                    return !m_commandQueue.empty() || !m_running;
                    });

                while (!m_commandQueue.empty()) {
                    auto cmd = std::move(m_commandQueue.front());
                    m_commandQueue.pop();
                    lock.unlock();
                    cmd->Execute();
                    lock.lock();
                }
            }
        }

    public:
        MixerImpl() {
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
            m_workerThread = std::jthread([this] { WorkerLoop(); });
        }

        ~MixerImpl() {
            {
                std::lock_guard lock(m_queueMutex);
                m_running = false;
            }
            m_queueCV.notify_all();
            m_workerThread.join();

            for (auto& [id, chunk] : m_sounds)
                Mix_FreeChunk(chunk);
            Mix_CloseAudio();
        }

        void LoadSound(const std::string& id, const std::string& path) {
            std::lock_guard lock(m_queueMutex);
            m_commandQueue.push(std::make_unique<LoadSoundCommand>(id, path, m_sounds));
            m_queueCV.notify_one();
        }

        void PlaySound(const std::string& id) {
            std::lock_guard lock(m_queueMutex);
            m_commandQueue.push(std::make_unique<PlaySoundCommand>(id, m_sounds));
            m_queueCV.notify_one();
        }
    };
}


dae::SoundService::SoundService()
    : m_mixerPimpl(std::make_unique<MixerImpl>()) {
}

dae::SoundService::~SoundService() = default;

void dae::SoundService::LoadSound(const std::string& id, const std::string& path) {
    m_mixerPimpl->LoadSound(id, path);
}

void dae::SoundService::PlaySound(const std::string& id) {
    m_mixerPimpl->PlaySound(id);
}