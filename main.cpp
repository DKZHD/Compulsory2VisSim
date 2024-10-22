#include "pch.h"
#include "src/Core.h"
#include "src/Math/Math.h"


int main()
{
	Core::GetInstance().Init();
	Core::GetInstance().Run();
}
