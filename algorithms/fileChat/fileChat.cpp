#include "fileChat.hpp"

File file;

std::string getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y.%m.%d %X");
    return ss.str();
}

void File::setPath(std::string path)
{
    this->path = path;
    int i = path.length() - 1;
    while (path[i] != '.')
    {
        i--;
    }
    extension = path.substr(i + 1, path.length() - i);
    i--;
    while (path[i] != '/' && i > 0)
    {
        i--;
    }
    name = path.substr(i, path.length() - i - extension.length() - 1);
    if (name[0] == '/')
    {
        name = name.substr(1, name.length() - 1);
    }
#if __KSI_DEBUG_LEVEL > 1
    std::cout << "> d2: Set name to " << name << std::endl;
    std::cout << "> d2: Set extension to " << extension << std::endl;
#endif // __KSI_DEBUG_LEVEL > 1
}

std::string File::getName() const
{
    return name;
}

std::string File::getPath() const
{
    return File::path;
}

std::string File::getExtension() const
{
    return extension;
}

int File::openStream()
{
    try
    {
        file = std::fstream(path, std::ios::in | std::ios::out |
                                      std::ios::binary);
        if (file.good())
        {
            file.seekg(0, std::ios::end);
            return 1;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return -1;
}

int File::close()
{
    if (file.good())
    {
        file.close();
        return 1;
    }
    return -1;
}

std::vector<char> File::readBytes()
{
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    if (size == 0)
    {
        return std::vector<char>();
    }
    char *buf = new char[size];
    file.read(buf, size);
#if __KSI_DEBUG_LEVEL > 1
    std::cout << "> d2: Read " << size << " bytes" << std::endl;
#endif // __KSI_DEBUG_LEVEL > 1
    std::vector<char> result;
    for (int i = 0; i < size; i++)
    {
        result.push_back(buf[i]);
    }
    delete[] buf;
    return result;
}

std::string File::read()
{
    auto buf = readBytes();
    for (int i = 0; i < buf.size() - 1; i++)
    {
        if (buf[i] == '\0')
        {
            buf[i] = '\n';
        }
    }
    return std::string(buf.data());
}

std::string File::getLastMessages(size_t numOfMsgs)
{
    auto buf = readBytes();
    if (buf.size() == 0)
    {
        return "";
    }
    std::vector<std::string> messages;
    std::string msg = "";
    for (int i = 0; i < buf.size() - 1; i++)
    {
        if (buf[i] == 0x00)
        {
            messages.push_back(msg);
            msg = "";
        }
        else
        {
            msg += buf[i];
        }
    }
    if (msg != "")
    {
        messages.push_back(msg);
    }
    std::string result = "";
    numOfMsgs = std::min(numOfMsgs, messages.size());
    for (int i = messages.size() - numOfMsgs; i < messages.size(); i++)
    {
        result += messages[i] + "\n";
    }
    return result;
}

int File::write(std::string text)
{
    file.write(text.c_str(), text.length() + 1);
#if __KSI_DEBUG_LEVEL > 1
    std::cout << "> d2: Wrote " << text.length() + 1
              << " bytes" << std::endl;
#endif // __KSI_DEBUG_LEVEL > 1
    return 1;
}

Message::Message(std::string date, std::string sender, std::string text)
{
    this->date = date;
    this->sender = sender;
    this->text = text;
}

Message::~Message() = default;

std::string Message::getDate() const
{
    return date;
}

std::string Message::getText() const
{
    return text;
}

std::string Message::getSender() const
{
    return sender;
}

std::string Message::toString() const
{
    std::stringstream ss;
    ss << date << " - " << sender << " - " << text;
    return ss.str();
}

void Message::setDate(std::string date)
{
    this->date = date;
}

void Message::setText(std::string text)
{
    this->text = text;
}

void Message::setSender(std::string sender)
{
    this->sender = sender;
}

unsigned long long Encryptor::hash(std::string str)
{
    unsigned long long hash = 0;
    auto str_c = str.c_str();
    for (; *str_c; str_c++)
        hash = (hash * 1664525) + (unsigned char)(*str_c) + 1013904223;
    return hash;
}

std::string Encryptor::hashToString(unsigned long long hash)
{
    std::stringstream ss;
    ss << hash;
    return ss.str();
}

std::string Encryptor::hashName(std::string name)
{
    return hashToString(hash(name));
}

int Server::writeMessage(Message msg)
{
    file.openStream();
    file.write(msg.toString());
    file.close();
    return 1;
}

std::string Server::getLastMessages(size_t numOfMsgs)
{
    file.openStream();
    std::string result = file.getLastMessages(numOfMsgs);
    file.close();
    return result;
}

Client::Client(std::string name)
{
    this->name = name;
}

std::string Client::getName() const
{
    return name;
}

void Client::setName(std::string name)
{
    this->name = name;
}

void Client::sendMessage(std::string message)
{
    Message msg = Message(getCurrentDateTime(),
                          Encryptor::hashName(name),
                          message);
    Server::writeMessage(msg);
}

std::string Client::requestMessages()
{
    return Server::getLastMessages(10);
}