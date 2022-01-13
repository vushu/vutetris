#pragma once
namespace bi {
    class PhysicsManager{
        public:
            // constructors, asssignment, destructor
            PhysicsManager();
            ~PhysicsManager();
            void addPhysicObject();

        private:

    };

    const float M2P=32.0f;
    const float P2M=1.0f/M2P;
}
