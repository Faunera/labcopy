export module FFunctionoid;
import std;

export 
{
	class Functionoid
	{
	public:
		virtual ~Functionoid() = 0;

		void call();

		virtual void custom() = 0;

		void addKey(int k = 0);

		void removeKey(int k = 0);

		void setState(int k = 0, bool pressed = false);

		std::unordered_map<int, bool> keys{};
	};
}

