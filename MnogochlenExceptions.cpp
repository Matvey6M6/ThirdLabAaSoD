#include "MnogochlenExceptions.hpp"
#include <cstring>

MnogochlenExceptions::MnogochlenExceptions() { cout << "An exception occured! " << endl; }
void MnogochlenExceptions::SetMessage(const char *Message)
{
    if (Message != nullptr && strcmp(Message, "") != 0)
        this->Message = Message;
}
void MnogochlenExceptions::PrintInfo() const
{
    cout << Message << endl;
}

MemoryError::MemoryError(const char *Message)
{
    SetMessage(Message);
    PrintInfo();
}

RangeError::RangeError(const char *Message)
{
    SetMessage(Message);
    PrintInfo();
}
