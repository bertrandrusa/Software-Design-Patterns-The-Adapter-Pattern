/**
 * CSC232 - Data Structures
 * Missouri State University, Fall 2020
 *
 * @file      google_test_runner.cpp
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation template.
 */

#include "csc232.h"
#include "QueueInterface.h"
#include "STLQueueToQueueAdapter.h"
#include "gtest/gtest.h"

/**
 * @brief Namespace to encapsulate course specific macros, declarations and definitions.
 */
namespace csc232
{
    static int possiblePoints{ 0 };
    static int earnedPoints{ 0 };
    static const int MAX_CORRECTNESS_PTS{ 2 };

    /**
     * @brief Base test fixture that sets up grading for this assignment.
     */
    class CSC232BaseTestFixture : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            ::testing::FLAGS_gtest_death_test_style = "threadsafe";
            AdditionalSetup();
            possiblePoints += 1;
        }

        void TearDown() override
        {
            if (!HasFailure())
            {
                earnedPoints += 1;
            }
        }

        virtual void AdditionalSetup()
        {
            /* template method for any customized additional setup */
        }

        // Reusable objects for each unit test in this test fixture and any of its children
    };

    // Run me to test your PrintTable function
    class PrintTestFixture : public CSC232BaseTestFixture
    {
    private:
        void AdditionalSetup() override
        {
            ::testing::internal::CaptureStdout();
        }
    protected:
        // Reusable objects for each unit test in this test fixture
        std::string test{ "This is a test" };
    };

    TEST_F( PrintTestFixture, DISABLED_PrintTest )
    {
        // Given some function that prints to stdout
        std::cout << test;
        // Expect the following to be captured
        std::string expected{ test };
        std::string actual{ testing::internal::GetCapturedStdout() };
        EXPECT_EQ( expected, actual );
    }

    // Extend the base test fixture as needed for various components under test...
    class CSC232ChildClassTestFixture : public CSC232BaseTestFixture
    {
    protected:
        // Reusable objects for each unit test in this test fixture
    };

    TEST_F( CSC232ChildClassTestFixture, DISABLED_ValidateFailedAssertionTest )
    {
        EXPECT_DEATH( {
            assert( false ); // some line(s) of code that will cause a failed assertion
        }, ".*failed.*" );
    }

    class STLQueueToQueueAdapterTestFixture : public CSC232BaseTestFixture
    {
        /**
         * @brief Axioms
         * (Queue()).isEmpty() = true
         * (Queue()).dequeue() = false
         * (Queue()).peekFront() = error
         * (aQueue.enqueue(item)).dequeue() => aQueue
         * (aQueue.enqueue(item)).peekFront() = item
         * (aQueue.enqueue(item)).isEmpty() = false
         * (aQueue.enqueue(item)).dequeue() = true
         */
    protected:
    };

    /**
     * @brief (Queue()).isEmpty() = true
     */
    TEST_F( STLQueueToQueueAdapterTestFixture, QueueIsInitiallyEmpty )
    {
        QueueInterface<std::string>* qPtr = new STLQueueToQueueAdapter<std::string>{std::queue<std::string>{}};
        ASSERT_TRUE(qPtr->isEmpty());
    }

    /**
     * @brief (Queue()).dequeue() = false
     */
    TEST_F( STLQueueToQueueAdapterTestFixture, DequeueEmptyQueueIsFalse )
    {
        QueueInterface<std::string>* qPtr = new STLQueueToQueueAdapter<std::string>{std::queue<std::string>{}};
        ASSERT_FALSE(qPtr->dequeue());
    }

    /**
     * @brief (Queue()).peekFront() = error
     */
    TEST_F( STLQueueToQueueAdapterTestFixture, PeekFronEmptyQueueIsError )
    {
        EXPECT_THROW({
            QueueInterface<std::string>* qPtr = new STLQueueToQueueAdapter<std::string>{std::queue<std::string>{}};
            std::string front{qPtr->peekFront()};
        }, std::logic_error);
    }

    /**
     * @brief (aQueue.enqueue(item)).dequeue() => aQueue
     */
    TEST_F( STLQueueToQueueAdapterTestFixture, EnqueueDequeueDoesntChangeQueue )
    {
        QueueInterface<std::string>* qPtr = new STLQueueToQueueAdapter<std::string>{std::queue<std::string>{}};
        qPtr->enqueue("test");
        qPtr->dequeue();
        ASSERT_TRUE(qPtr->isEmpty());
    }

    /**
     * @brief (aQueue.enqueue(item)).peekFront() = item
     */
    TEST_F( STLQueueToQueueAdapterTestFixture, EnqueuePeekIsItem )
    {
        QueueInterface<std::string>* qPtr = new STLQueueToQueueAdapter<std::string>{std::queue<std::string>{}};
        qPtr->enqueue("test");
        ASSERT_EQ("test", qPtr->peekFront());
    }

    /**
     * @brief (aQueue.enqueue(item)).isEmpty() = false
     */
    TEST_F( STLQueueToQueueAdapterTestFixture, EnqueueCreatesNonEmptyQueue )
    {
        QueueInterface<std::string>* qPtr = new STLQueueToQueueAdapter<std::string>{std::queue<std::string>{}};
        qPtr->enqueue("test");
        ASSERT_FALSE(qPtr->isEmpty());
    }

    /**
     * @brief (aQueue.enqueue(item)).dequeue() = true
     */
    TEST_F( STLQueueToQueueAdapterTestFixture, EnqueueDequeueIsTrue )
    {
        QueueInterface<std::string>* qPtr = new STLQueueToQueueAdapter<std::string>{std::queue<std::string>{}};
        qPtr->enqueue("test");
        ASSERT_TRUE(qPtr->dequeue());
    }
} // end namespace

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest( &argc, argv );
    int result{ RUN_ALL_TESTS() };
    std::cout << std::fixed << std::setprecision( 2 );
    std::cout << "\n\n";
    std::cout << std::left << std::setw( 21 ) << "Earned Points:"
              << std::right << std::setw( 5 ) << static_cast<double>(csc232::earnedPoints) << std::endl;
    std::cout << std::left << std::setw( 21 ) << "Possible Points:"
              << std::right << std::setw( 5 ) << static_cast<double>(csc232::possiblePoints) << std::endl;
    double percentCorrect{ static_cast<double>(csc232::earnedPoints) / csc232::possiblePoints };
    double correctnessPoints{ csc232::possiblePoints != 0 ? percentCorrect * csc232::MAX_CORRECTNESS_PTS
                                                          : 0 };
    std::cout << std::left << std::setw( 21 ) << "Correctness Points:"
              << std::right << std::setw( 5 ) << correctnessPoints << std::endl;
    return result;
}
