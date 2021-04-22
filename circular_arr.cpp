#pragma once
#include "typedefs.h"
#include <stdlib.h>

template<typename T>
struct CircularArray
{
private:
    T *_data;
    u32 _size;
    u32 _begin;
    u32 _end;
    bool _full;
public:
    CircularArray(u32 size) : _size(size), _begin(0), _end(0), _full(false)
    {
        _data = (T *) malloc(size * sizeof(T));
    }

    void push_back(T item)
    {
        _data[_end] = item;
        ++_end;
        if(_end == _size) _end = 0;
        if(_full)
        {
            ++_begin;
            if(_begin == _size) _begin = 0;
        }
        else
        {
            if(_end == _begin) _full = true;
        }
    }

    T& operator[](u32 index)
    {
        return get(index);
    }

    T& get(u32 index)
    {
        index = (_begin + index) % _size;
        return _data[index];
    }

    T& back()
    {
        return _data[_end - 1];
    }

    T& front()
    {
        return _data[_begin];
    }

    void pop_front()
    {
        if(empty()) return;
        _begin++;
        if(_begin == _size) _begin = 0;
        _full = false;
    }

    void pop_back()
    {
        if(empty()) return;
        if(_end == 0) _end = _size;
        _end--;
        _full = false;
    }

    u32 size()
    {
        if(_end >= _begin && !_full) return _end - _begin;
        return _size - (_begin - _end);
    }

    bool empty()
    {
        return _end == _begin && !_full;
    }

};

