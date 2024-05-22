/**
 * @brief Listing 13-1: The Queue interface.
 * @authors Frank M. Carrano and Timothy M. Henry
 * @file QueueInterface.h
 * @copyright Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
 */

#ifndef QUEUE_INTERFACE_
#define QUEUE_INTERFACE_

/**
 * @brief In the Adapter pattern, this interface represents the Target.
 * @tparam ItemType the type of item held in this queue
 */
template<typename ItemType>
class QueueInterface
{
public:
    /**
     * @brief Sees whether this queue is empty.
     * @return True if the queue is empty, or false if not.
     */
   virtual bool isEmpty() const = 0;
   
   /**
    * @brief Adds a new entry to the back of this queue.
    * @post If the operation was successful, newEntry is at the back of the queue.
    * @param newEntry  The object to be added as a new entry.
    * @return True if the addition is successful or false if not.
    */
   virtual bool enqueue(const ItemType& newEntry) = 0;
   
   /**
    * @brief Removes the front of this queue.
    * @post If the operation was successful, the front of the queue has been removed.
    * @return True if the removal is successful or false if not.
    */
   virtual bool dequeue() = 0;
   
   /**
    * @brief Returns the front of this queue.
    * @pre The queue is not empty.
    * @post The front of the queue has been returned, and the queue is unchanged.
    * @return The front of the queue.
    */
   virtual ItemType peekFront() const = 0;
   
   /**
    * @brief Destroys object and frees memory allocated by object.
    */
   virtual ~QueueInterface() = default;
}; // end QueueInterface

#endif
