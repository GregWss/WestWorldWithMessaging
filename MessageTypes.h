#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_CanYouMove,
  Msg_IWontMove,
  Msg_Hit,
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

	return "CanYouMove";

  case 3:

	  return "IWontMove";

  case 4:

	  return "Hit";

  case 5:

	  return "KnockOut";

  case 6:

	  return "Miss";

  default:

    return "Not recognized!";
  }
}

#endif