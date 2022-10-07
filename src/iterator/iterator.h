#pragma once

class Iterator
{
public:
    virtual ~Iterator() {}
    
    virtual void first() 
    {
        throw std::string("Unable to call first, override this function if needed."); 
    }

    virtual Shape* currentItem() 
    {
        throw std::string("Unable to call currentItem, override this function if needed."); 
    }
    
    virtual void next()
    {
        throw std::string("Unable to call next, override this function if needed."); 
    }

    virtual bool isDone() const 
    {
        return true;
    }
};

