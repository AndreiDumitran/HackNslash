#include "Animation.h"

Animation::Animation(string name)
{
    this->name = name;
}

int Animation::GetNextFrameNumber(int frameNumber)
{
    return (frameNumber + 1) % frames.size();
}

Frame* Animation::GetNextFrame(Frame* frame)
{
    return GetFarame(GetNextFrameNumber(frame->frameNumber));
}

int Animation::GetEndFrameNumber()
{
    return frames.size() - 1;
}

Frame* Animation::GetFarame(int frameNumber)
{
    if (frames.size() == 0)
        return NULL;
    list<Frame>::iterator i = frames.begin();

    for (int j = 0; j < frameNumber && j < frames.size() - 1; j++)
    {
        i++;
    }
    Frame* frame = &(*i);

    return frame;
}

void Animation::LoadAnimation(ifstream& file, list<DataGroupType>& groupTypes)
{
    getline(file, name);
    string buffer;
    getline(file, buffer);
    stringstream ss;
    buffer = Globals::clipOffDataHeader(buffer);
    ss << buffer;
    int numberOfFrames;
    ss >> numberOfFrames;
    for (int i = 0; i < numberOfFrames; i++) {
        Frame newFrame;
        newFrame.LoadFrame(file, groupTypes);
        frames.push_back(newFrame);
    }
}
