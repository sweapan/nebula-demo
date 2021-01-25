#include "camera.h"

namespace Demo {
    void
    Camera::Setup(const Math::point& defaultEyePos, const Math::vector& defaultEyeVec)
    {
        this->defaultEyePos = defaultEyePos;
        this->defaultEyeVec = defaultEyeVec;
        this->position = this->defaultEyePos;
        this->viewAngles.set(this->defaultEyeVec);
    }

    void
    Camera::Reset()
    {
        this->viewAngles.set(this->defaultEyeVec);
        this->position = this->defaultEyePos;
    }

    void
    Camera::Update(PlayerInput input)
    {
        auto& io = ImGui::GetIO();
        //Rotate counterclockwise
        if (input.countercwY)
        {
            this->viewAngles.rho += rotationSpeed;
        }
        //Rotate clockwise
        if (input.clockwiseY)
        {
            this->viewAngles.rho -= rotationSpeed;
        }
        //Rotate up
        if (input.countercwX)
        {
            this->viewAngles.theta += rotationSpeed;
        }
        //Rotate down
        if (input.clockwiseX)
        {
            this->viewAngles.theta -= rotationSpeed;
        }
        Math::mat4 xMat = Math::rotationx(this->viewAngles.theta - (N_PI * 0.5f));
        Math::mat4 yMat = Math::rotationy(this->viewAngles.rho);
        this->transform = xMat * yMat;

        float currentMoveSpeed = moveSpeed;
        Math::vec4 translation = Math::vec4(0, 0, 0, 0);
        if (input.forward)
        {
            position.x -= Math::sin(this->viewAngles.rho) * currentMoveSpeed;
            position.z -= Math::cos(this->viewAngles.rho) * currentMoveSpeed;
        }
        if (input.backward)
        {
            position.x += Math::sin(this->viewAngles.rho) * currentMoveSpeed;
            position.z += Math::cos(this->viewAngles.rho) * currentMoveSpeed;
        }
        if (input.right)
        {
            translation.x += currentMoveSpeed;
        }
        if (input.left)
        {
            translation.x -= currentMoveSpeed;
        }
        if (input.up)
        {
            position.y += currentMoveSpeed;
        }
        if (input.down)
        {
            position.y -= currentMoveSpeed;
        }

        if (input.reset) 
        {
            this->Reset();
        }
        translation = this->transform * translation;
        this->position += xyz(translation);

        this->transform.position = Math::point(this->position);
    }
}