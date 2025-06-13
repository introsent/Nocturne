#pragma once
#include "Command.h"
#include "NameEntryComponent.h"

class NameEntryUpCommand : public dae::Command {
public:
    NameEntryUpCommand(NameEntryComponent* p) : m_pNameEntry(p) {}
    void Execute() override { m_pNameEntry->HandleUp(); }
private:
    NameEntryComponent* m_pNameEntry;
};
class NameEntryDownCommand : public dae::Command {
public:
    NameEntryDownCommand(NameEntryComponent* p) : m_pNameEntry(p) {}
    void Execute() override { m_pNameEntry->HandleDown(); }
private:
    NameEntryComponent* m_pNameEntry;
};
class NameEntryLeftCommand : public dae::Command {
public:
    NameEntryLeftCommand(NameEntryComponent* p) : m_pNameEntry(p) {}
    void Execute() override { m_pNameEntry->HandleLeft(); }
private:
    NameEntryComponent* m_pNameEntry;
};
class NameEntryRightCommand : public dae::Command {
public:
    NameEntryRightCommand(NameEntryComponent* p) : m_pNameEntry(p) {}
    void Execute() override { m_pNameEntry->HandleRight(); }
private:
    NameEntryComponent* m_pNameEntry;
};
class NameEntrySelectCommand : public dae::Command {
public:
    NameEntrySelectCommand(NameEntryComponent* p) : m_pNameEntry(p) {}
    void Execute() override { m_pNameEntry->HandleSelect(); }
private:
    NameEntryComponent* m_pNameEntry;
};

