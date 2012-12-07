#ifndef KEYCONTROL_HEADER
#define KEYCONTROL_HEADER


class KeyControl {

protected:

  int keyCode;
  bool released;
  int timer; // Update every tick while the key is pressed
  int delay; // Number of ticks to wait until the action for this key is performed again

public:

  KeyControl(int aKey);

  void setDelay(bool theDelay);
  bool isPressed();
};


#endif
