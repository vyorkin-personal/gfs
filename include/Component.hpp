#pragma once

namespace gfs {
    class Component {
        public:
            virtual ~Component() = 0;

            int getId() const {
                return id;
            }

            bool operator == (const Component& other) const {
                return getId() == other.getId();
            }

        protected:
            Component();

        private:
            int id;
            static int nextId;
    };
}
