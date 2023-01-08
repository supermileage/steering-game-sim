#ifndef _STEERING_UTIL_H_
#define _STEERING_UTIL_H_

#include <string>

namespace util {

	/**
	 * @brief abstract base: encapsulates a method invocation with possible execution arguments
	 */
	typedef void* CommandArgs;
	class Command {
		public:
			virtual ~Command() { }
			virtual void execute(CommandArgs args) = 0;
	};

	/**
	 * @brief encapsulates a callback function with possible args T
	 * 
	 * @tparam T type of param for callback function
	 */
	template <class T>
	class FunctionalCallback : public Command {
		public:
			FunctionalCallback(void (*callback)(const T)) : _callback(callback) { }
			~FunctionalCallback() { }
			virtual void execute(CommandArgs args) {
				_callback(*((T*)args));
			}

		private:
			void (*_callback)(const T);
	};

	/**
	 * @brief encapsulates a callback method for type T
	 * 
	 * @tparam T class which implements method
	 * @tparam R param for T::method
	 */
	template <class T, class R>
	class Delegate : public Command {
		public:
			Delegate(T* owner, void (T::*callback)(const R)) : _owner(owner), _callback(callback) { }
			~Delegate() { }
			void execute(CommandArgs args) override {
				(_owner->*_callback)(*((R*)args));
			}
		private:
			T* _owner;
			void (T::*_callback)(const R);
	};

	struct Vec2 {
        float x;
        float y;

        bool operator!=(Vec2 vec) {
            return x != vec.x || y != vec.y;
        }
    };

    struct Pos {
        int32_t x;
        int32_t y;
    };

    struct Collision {
        const std::string& obj1;
        const std::string& obj2;

        Collision(const std::string& n1, const std::string& n2) : obj1(n2), obj2(n2) { }
    };

    int32_t computeDistance(Pos p1, Pos p2);
}

#endif