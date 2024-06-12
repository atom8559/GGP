#pragma once
#include "Model.h"

enum CharacterDirection {
    UP,
    LEFT,
    DOWN,
    RIGHT
};

class Character : public Model {
public:
    Character(const std::filesystem::path& filePath);
    ~Character();

    void HandleInput(const InputDirections& directions, float deltaTime);
    void Update(float deltaTime);

private:
    constexpr static XMVECTORF32 DEFAULT_FORWARD = { 0.0f, 0.0f, 1.0f, 0.0f };
    constexpr static XMVECTORF32 DEFAULT_RIGHT = { 1.0f, 0.0f, 0.0f, 0.0f };

    XMVECTOR m_targetPosition;
    XMVECTOR m_currentPosition;
    float m_moveLeftRight;
    float m_moveBackForward;

    CharacterDirection m_currentRotation;
    float m_movementSpeed;
};

