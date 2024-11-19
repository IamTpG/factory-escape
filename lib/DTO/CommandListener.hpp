#ifndef COMMAND_LISTENER_HPP
#define COMMAND_LISTENER_HPP

// Prototype class for any class that receives commands directly from the user
class CommandListener {
public:
    CommandListener()           { /* do nothing */ }
    virtual ~CommandListener()  { /* do nothing */ }

public:
    // Character class
    virtual void goLeft()       { /* do nothing */ }
    virtual void goRight()      { /* do nothing */ }
    virtual void goUp()         { /* do nothing */ }
    virtual void goNowhere()    { /* do nothing */ }
    
    // Platform class
    virtual void drag()         { /* do nothing */ }
};

#endif // COMMAND_LISTENER_HPP
