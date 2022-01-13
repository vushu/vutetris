#pragma once

namespace bi  {
    class Component {
        public:
            // constructors, asssignment, destructor
            Component();
            ~Component();

            void update(float dt);
            void start();

        protected:

        private:

    };
}
