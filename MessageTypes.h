#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_UTalkingToMe,
  Msg_CanYouMove,
  Msg_Punch,
  Msg_KnockOut,
  Msg_Miss
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

  case 2:

	return "UTalkingToMe";

  case 3:

	  return "CanYouMove";

  default:

    return "Not recognized!";
  }
}

#endif