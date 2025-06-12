#include "SoundService.h"
#include <SDL_mixer.h>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <ranges>

#include "Command.h"
#include "LoadSoundCommand.h"
#include "PlaySoundCommand.h"
#include "SoundInfo.h"

namespace dae
{
    class SoundService::MixerImpl {
        std::mutex m_queueMutex;
        std::condition_variable m_queueCV;
        std::queue<std::unique_ptr<Command>> m_commandQueue;
        std::jthread m_workerThread;

        std::mutex m_soundMutex;
        std::unordered_map<std::string, SoundInfo> m_soundInfo;

        bool m_running = true;

        void WorkerLoop() {
            while (m_running) {
                std::queue<std::unique_ptr<Command>> localQueue;

                {
                    std::unique_lock lock(m_queueMutex);
                    m_queueCV.wait(lock, [this] {
                        return !m_commandQueue.empty() || !m_running;
                        });

                    if (!m_running) break;
                    std::swap(localQueue, m_commandQueue);
                }

                while (!localQueue.empty()) {
                    auto cmd = std::move(localQueue.front());
                    localQueue.pop();
                    cmd->Execute();
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

            std::lock_guard soundLock(m_soundMutex);
            for (auto& [id, info] : m_soundInfo) {
                if (info.chunk) Mix_FreeChunk(info.chunk);
            }
            Mix_CloseAudio();
        }

        void RegisterSound(const std::string& id, const std::string& path) {
            std::lock_guard lock(m_soundMutex);
            if (m_soundInfo.contains(id)) return; // Already registered

            m_soundInfo[id] = SoundInfo{ path, nullptr };

            std::lock_guard queueLock(m_queueMutex);
            m_commandQueue.push(std::make_unique<LoadSoundCommand>(id, m_soundInfo, m_soundMutex));
            m_queueCV.notify_one();
        }

        void PlaySound(const std::string& id) {
            std::lock_guard queueLock(m_queueMutex);
            m_commandQueue.push(std::make_unique<PlaySoundCommand>(id, m_soundInfo, m_soundMutex));
            m_queueCV.notify_one();
        }
    };

    SoundService::SoundService() : m_mixerPimpl(std::make_unique<MixerImpl>()) {}
    SoundService::~SoundService() = default;
    void SoundService::RegisterSound(const std::string& id, const std::string& path) { m_mixerPimpl->RegisterSound(id, path); }
    void SoundService::PlaySound(const std::string& id) { m_mixerPimpl->PlaySound(id); }
}