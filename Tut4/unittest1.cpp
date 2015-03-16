#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\RootFinder\RootFinder.h"
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tut4
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			CRootFinder rooter;
			Assert::AreEqual(
				//Expected value:
				0.0,
				//Actual value:
				rooter.SquareRoot(0.0),
				//Tolerance:
				0.01,
				//Message:
				L"Basic test failed",
				// Line number
				LINE_INFO());
		}

		TEST_METHOD(RangeTest)
		{
			CRootFinder rooter;
			for (double v = 1e-6; v < 1e6; v = v*3.2)
			{
				double actual = rooter.SquareRoot(v*v);
				Assert::AreEqual(v, actual, v / 1000);
			}
		}

		TEST_METHOD(NegativeRangeTest)
		{
			wchar_t message[200];
			CRootFinder rooter;
			for (double v = -0.1; v > -3.0; v = v - 0.5)
			{
				try
				{
					// Should raise an exception:
					double result = rooter.SquareRoot(v);

					_swprintf(message, L"No exception for input %g", v);
					Assert::Fail(message, LINE_INFO());
				}
				catch (std::out_of_range ex)
				{
					continue; // correct exception.
				}
				catch (...)
				{
					_swprintf(message, L"Incorrect exception for %g", v);
					Assert::Fail(message, LINE_INFO());
				}
			}
		}

	};
}