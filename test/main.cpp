#include <windows.h>

#define BELT_COM_NO_LEAK_DETECTION
#include <moderncom/interfaces.h>

#include <iostream>

// Declare sample interface

BELT_DEFINE_INTERFACE(ISampleInterface, "{AB9A7AF1-6792-4D0A-83BE-8252A8432B45}")
{
	virtual int sum(int a, int b) const noexcept = 0;
	virtual int get_answer() const noexcept = 0;
};

// Define implementation

class __declspec(novtable) sample_object :
	public belt::com::object<sample_object, ISampleInterface>
{
	int default_answer;

	// ISampleInterface implementation
	virtual int sum(int a, int b) const noexcept override
	{
		return a + b;
	}

	virtual int get_answer() const noexcept override
	{
		return default_answer;
	}

public:
	sample_object(int default_answer) noexcept :
		default_answer{ default_answer }
	{}
};

int main()
{
	// Create new instance of sample_object and get its' ISampleInterface interface pointer

	{
		auto obj = sample_object::create_instance(42).to_ptr();

		std::cout << obj->sum(obj->get_answer(), 5);
	}
}
