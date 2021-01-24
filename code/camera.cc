#include "camera.h"

namespace Demo {
    void
    Camera::Setup(const Math::point& defaultEyePos, const Math::vector& defaultEyeVec)
    {
        this->defaultEyePos = defaultEyePos;
        this->defaultEyeVec = defaultEyeVec;
        this->position = this->defaultEyePos;
        this->viewAngles.set(this->defaultEyeVec);
        this->Update();
    }

    void
    Camera::Reset()
    {
        this->viewAngles.set(this->defaultEyeVec);
        this->position = this->defaultEyePos;
    }

    void
    Camera::Update()
    {
        auto& io = ImGui::GetIO();
        //Rotate counterclockwise
        if (io.KeysDown[Input::Key::A])
        {
            this->viewAngles.rho += rotationSpeed;
        }
        //Rotate clockwise
        if (io.KeysDown[Input::Key::D])
        {
            this->viewAngles.rho -= rotationSpeed;
        }
        //Rotate up
        if (io.KeysDown[Input::Key::W])
        {
            this->viewAngles.theta += rotationSpeed;
        }
        //Rotate down
        if (io.KeysDown[Input::Key::S])
        {
            this->viewAngles.theta -= rotationSpeed;
        }
        Math::mat4 xMat = Math::rotationx(this->viewAngles.theta - (N_PI * 0.5f));
        Math::mat4 yMat = Math::rotationy(this->viewAngles.rho);
        this->transform = xMat * yMat;

        float currentMoveSpeed = moveSpeed;
        Math::vec4 translation = Math::vec4(0, 0, 0, 0);
        if (io.KeysDown[Input::Key::Up])
        {
            position.x -= Math::sin(this->viewAngles.rho) * currentMoveSpeed;
            position.z -= Math::cos(this->viewAngles.rho) * currentMoveSpeed;
        }
        if (io.KeysDown[Input::Key::Down])
        {
            position.x += Math::sin(this->viewAngles.rho) * currentMoveSpeed;
            position.z += Math::cos(this->viewAngles.rho) * currentMoveSpeed;
        }
        if (io.KeysDown[Input::Key::Right])
        {
            translation.x += currentMoveSpeed;
        }
        if (io.KeysDown[Input::Key::Left])
        {
            translation.x -= currentMoveSpeed;
        }
        if (io.KeysDown[Input::Key::RightShift])
        {
            position.y += currentMoveSpeed;
        }
        if (io.KeysDown[Input::Key::RightControl])
        {
            position.y -= currentMoveSpeed;
        }

        if (io.KeysDown[Input::Key::R]) 
        {
            this->Reset();
        }
        translation = this->transform * translation;
        this->position += xyz(translation);

        this->transform.position = Math::point(this->position);
    }
}