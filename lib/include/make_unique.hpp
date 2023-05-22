#pragma once

#include <utility>
#include <memory>

/**
 * @brief Creates a new unique_ptr object with the given arguments.
 * 
 * @tparam T The type of object to create.
 * @tparam Args The types of arguments to pass to the object's constructor.
 * @param args The arguments to pass to the object's constructor.
 * @return A unique_ptr object that owns the newly created object.
 */
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}