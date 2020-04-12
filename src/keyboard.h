#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KB_PORT 0x60

//#define SCANCODE_SET_1
//#define KEY_ESC 0x43
//#define KEY_1 0x41
//#define KEY_2 0x3f
//#define KEY_3 0x3d
//#define KEY_4 0x3b
//#define KEY_5 0x3c
//#define KEY_6 0x58
//#define KEY_7 0x64
//#define KEY_8 0x44
//#define KEY_9 0x42
//#define KEY_0 0x40
//#define KEY_MINUS 0x3e
//#define KEY_EQUALS 0x0f
//#define KEY_BACKSPACE 0x29
//#define KEY_TAB 0x59
//#define KEY_Q 0x65
//#define KEY_W 0x38
//#define KEY_E 0x2a
//#define KEY_R 0x70
//#define KEY_T 0x1d
//#define KEY_Y 0x10
//#define KEY_U 0x02
//#define KEY_I 0x5a
//#define KEY_O 0x66
//#define KEY_P 0x71
//#define KEY_SQUARE_BRACKET_OPEN 0x2c
//#define KEY_SQUARE_BRACKET_CLOSE 0x1f
//#define KEY_ENTER 0x1e
//#define KEY_LCTRL 0x11
//#define KEY_A 0x03
//#define KEY_S 0x5b
//#define KEY_D 0x67
//#define KEY_F 0x2e
//#define KEY_G 0x2d
//#define KEY_H 0x20
//#define KEY_J 0x12
//#define KEY_K 0x05
//#define KEY_L 0x04
//#define KEY_SEMICOLON 0x5c
//#define KEY_QUOTE 0x68
//#define KEY_BACKTICK 0x39
//#define KEY_LSHIFT 0x2f
//#define KEY_BACKSLASH 0x21
//#define KEY_Z 0x14
//#define KEY_X 0x13
//#define KEY_C 0x06
//#define KEY_V 0x5d
//#define KEY_B 0x69
//#define KEY_N 0x31
//#define KEY_M 0x30
//#define KEY_COMMA 0x23
//#define KEY_PERIOD 0x22
//#define KEY_FORESLASH 0x15
//#define KEY_RSHIFT 0x07
//#define KEY_KP_MUL 0x5e
//#define KEY_LALT 0x6a
//#define KEY_SPACE 0x72
//#define KEY_CAPSLOCK 0x32
//#define KEY_F1 0x24
//#define KEY_F2 0x16
//#define KEY_F3 0x07
//#define KEY_F4 0x09
//#define KEY_F5 0x5f
//#define KEY_F6 0x6b
//#define KEY_F7 0x33
//#define KEY_F8 0x25
//#define KEY_F9 0x17
//#define KEY_F10 0x18
//#define KEY_NUMLOCK 0x0b
//#define KEY_SCRL_LOCK 0x0a
//#define KEY_KP_7 0x60
//#define KEY_KP_8 0x6c
//#define KEY_KP_9 0x34
//#define KEY_KP_MINUS 0x35
//#define KEY_KP_4 0x26
//#define KEY_KP_5 0x27
//#define KEY_KP_6 0x19
//#define KEY_KP_PLUS 0x0c
//#define KEY_KP_1 0x61
//#define KEY_KP_2 0x6d
//#define KEY_KP_3 0x73
//#define KEY_KP_0 0x28
//#define KEY_KP_DOT 0x74
//#define SYSRQ_ALT 0x1a
//#define KEY_F11 0x6e
//#define KEY_F12 0x3a
//#define KEY_RALT 0xe0 0x6a
//#define KEY_RCTRL 0xe0 0x11
//#define KEY_INSERT 0xe0 0x28
//#define KEY_DELETE 0xe0 0x74
//#define KEY_HOME 0xe0 0x60
//#define KEY_END 0xe0 0x61
//#define KEY_PGUP 0xe0 0x34
//#define KEY_PGDN 0xe0 0x73
//#define KEY_LEFT 0xe0 0x26
//#define KEY_UP 0xe0 0x6c
//#define KEY_DOWN 0xe0 0x6d
//#define KEY_RIGHT 0xe0 0x19
//#define KEY_KP_FORESLASH 0xe0 0x15
//#define KEY_KP_ENTER 0xe0 0x1e
//#define KEY_PRTSCR 0xe0 0x5e
//#define KEY_PAUSE 0xe1 0x11 0x0b
//#define KEY_CTRL_BRK 0xe0 0x0a
//#define KEY_LWIN 0xe0 0x1b
//#define KEY_RWIN 0xe0 0x75
//#define KEY_MENU 0xe0 0x2b
//#define KEY_SLEEP 0xe0 0x76
//#define KEY_POWER 0xe0 0x63
//#define KEY_WAKE 0xe0 0x78

#define SCANCODE_SET_2
#define KEY_ESC 0x01
#define KEY_1 0x02
#define KEY_2 0x03
#define KEY_3 0x04
#define KEY_4 0x05
#define KEY_5 0x06
#define KEY_6 0x07
#define KEY_7 0x08
#define KEY_8 0x09
#define KEY_9 0x0a
#define KEY_0 0x0b
#define KEY_MINUS 0x0c
#define KEY_EQUALS 0x0d
#define KEY_BACKSPACE 0x0e
#define KEY_TAB 0x0f
#define KEY_Q 0x10
#define KEY_W 0x11
#define KEY_E 0x12
#define KEY_R 0x13
#define KEY_T 0x14
#define KEY_Y 0x15
#define KEY_U 0x16
#define KEY_I 0x17
#define KEY_O 0x18
#define KEY_P 0x19
#define KEY_SQUARE_BRACKET_OPEN 0x1a
#define KEY_SQUARE_BRACKET_CLOSE 0x1b
#define KEY_ENTER 0x1c
#define KEY_LCTRL 0x1d
#define KEY_A 0x1e
#define KEY_S 0x1f
#define KEY_D 0x20
#define KEY_F 0x21
#define KEY_G 0x22
#define KEY_H 0x23
#define KEY_J 0x24
#define KEY_K 0x25
#define KEY_L 0x26
#define KEY_SEMICOLON 0x27
#define KEY_QUOTE 0x28
#define KEY_BACKTICK 0x29
#define KEY_LSHIFT 0x2a
#define KEY_BACKSLASH 0x2b
#define KEY_Z 0x2c
#define KEY_X 0x2d
#define KEY_C 0x2e
#define KEY_V 0x2f
#define KEY_B 0x30
#define KEY_N 0x31
#define KEY_M 0x32
#define KEY_COMMA 0x33
#define KEY_PERIOD 0x34
#define KEY_FORESLASH 0x35
#define KEY_RSHIFT 0x36
#define KEY_KP_MUL 0x37
#define KEY_LALT 0x38
#define KEY_SPACE 0x39
#define KEY_CAPSLOCK 0x3a
#define KEY_F1 0x3b
#define KEY_F2 0x3c
#define KEY_F3 0x3d
#define KEY_F4 0x3e
#define KEY_F5 0x3f
#define KEY_F6 0x40
#define KEY_F7 0x41
#define KEY_F8 0x42
#define KEY_F9 0x43
#define KEY_F10 0x44
#define KEY_NUMLOCK 0x45
#define KEY_SCRL_LOCK 0x46
#define KEY_KP_7 0x47
#define KEY_KP_8 0x48
#define KEY_KP_9 0x49
#define KEY_KP_MINUS 0x4a
#define KEY_KP_4 0x4b
#define KEY_KP_5 0x4c
#define KEY_KP_6 0x4d
#define KEY_KP_PLUS 0x4e
#define KEY_KP_1 0x4f
#define KEY_KP_2 0x50
#define KEY_KP_3 0x51
#define KEY_KP_0 0x52
#define KEY_KP_DOT 0x53
#define SYSRQ_ALT 0x54
#define KEY_F11 0x57
#define KEY_F12 0x58
#define KEY_RALT 0xe0 0x38
#define KEY_RCTRL 0xe0 0x1d
#define KEY_INSERT 0xe0 0x52
#define KEY_DELETE 0xe0 0x53
#define KEY_HOME 0xe0 0x47
#define KEY_END 0xe0 0x4f
#define KEY_PGUP 0xe0 0x49
#define KEY_PGDN 0xe0 0x51
#define KEY_LEFT 0xe0 0x4b
#define KEY_UP 0xe0 0x48
#define KEY_DOWN 0xe0 0x50
#define KEY_RIGHT 0xe0 0x4d
#define KEY_KP_FORESLASH 0xe0 0x35
#define KEY_KP_ENTER 0xe0 0x1c
#define KEY_PRTSCR 0xe0 0x37
#define KEY_CTRL_BRK 0xe0 0x46
#define KEY_LWIN 0xe0 0x5b
#define KEY_RWIN 0xe0 0x5c
#define KEY_MENU 0xe0 0x5d
#define KEY_SLEEP 0xe0 0x5f
#define KEY_POWER 0xe0 0x5e
#define KEY_WAKE 0xe0 0x63
#define KEY_PAUSE 0xe1 0x1d 0x45
//
//#define SCANCODE_SET_3
//#define KEY_NUMLOCK 0x01
//#define KEY_1 0x02
//#define KEY_2 0x03
//#define KEY_3 0x04
//#define KEY_4 0x05
//#define KEY_5 0x06
//#define KEY_6 0x07
//#define KEY_7 0x08
//#define KEY_8 0x09
//#define KEY_9 0x0a
//#define KEY_0 0x0b
//#define KEY_MINUS 0x0c
//#define KEY_EQUALS 0x0d
//#define KEY_BACKSPACE 0x0e
//#define KEY_TAB 0x0f
//#define KEY_Q 0x10
//#define KEY_W 0x11
//#define KEY_E 0x12
//#define KEY_R 0x13
//#define KEY_T 0x14
//#define KEY_Y 0x15
//#define KEY_U 0x16
//#define KEY_I 0x17
//#define KEY_O 0x18
//#define KEY_P 0x19
//#define KEY_SQUARE_BRACKET_OPEN 0x1a
//#define KEY_SQUARE_BRACKET_CLOSE 0x1b
//#define KEY_ENTER 0x1c
//#define KEY_CAPSLOCK 0x1d
//#define KEY_A 0x1e
//#define KEY_S 0x1f
//#define KEY_D 0x20
//#define KEY_F 0x21
//#define KEY_G 0x22
//#define KEY_H 0x23
//#define KEY_J 0x24
//#define KEY_K 0x25
//#define KEY_L 0x26
//#define KEY_SEMICOLON 0x27
//#define KEY_QUOTE 0x28
//#define KEY_BACKTICK 0x29
//#define KEY_LSHIFT 0x2a
//#define KEY_Z 0x2c
//#define KEY_X 0x2d
//#define KEY_C 0x2e
//#define KEY_V 0x2f
//#define KEY_B 0x30
//#define KEY_N 0x31
//#define KEY_M 0x32
//#define KEY_COMMA 0x33
//#define KEY_PERIOD 0x34
//#define KEY_FORESLASH 0x35
//#define KEY_RSHIFT 0x36
//#define KEY_KP_PLUS 0x37
//#define KEY_LCTRL 0x38
//#define KEY_SPACE 0x39
//#define KEY_RCTRL 0x3a
//#define KEY_KP_FORESLASH 0x45
//#define KEY_KP_MUL 0x46
//#define KEY_KP_7 0x47
//#define KEY_KP_8 0x48
//#define KEY_KP_9 0x49
//#define KEY_KP_4 0x4b
//#define KEY_KP_5 0x4c
//#define KEY_KP_6 0x4d
//#define KEY_KP_ENTER 0x4e
//#define KEY_KP_1 0x4f
//#define KEY_KP_2 0x50
//#define KEY_KP_3 0x51
//#define KEY_KP_0 0x52
//#define KEY_KP_DOT 0x53
//#define KEY_KP_MINUS 0x54
//#define KEY_DOWN 0x55
//#define KEY_LEFT 0x56
//#define KEY_F1 0x58
//#define KEY_F2 0x59
//#define KEY_F3 0x5a
//#define KEY_F4 0x5b
//#define KEY_F5 0x5c
//#define KEY_F6 0x5d
//#define KEY_F7 0x5e
//#define KEY_F8 0x5f
//#define KEY_F9 0x60
//#define KEY_F10 0x61
//#define KEY_F11 0x62
//#define KEY_F12 0x63
//#define KEY_ESC 0x64
//#define KEY_PRTSCR 0x6e
//#define SYSRQ_ALT 0x6e
//#define KEY_PGUP 0x6f
//#define KEY_LALT 0x71
//#define KEY_RALT 0x72
//#define KEY_BACKSLASH 0x75
//#define KEY_SCRL_LOCK 0x76
//#define KEY_PAUSE 0x77
//#define KEY_CTRL_BRK 0x77
//#define KEY_UP 0x78
//#define KEY_DELETE 0x79
//#define KEY_END 0x7a
//#define KEY_INSERT 0x7b
//#define KEY_RIGHT 0x7d
//#define KEY_PGDN 0x7e
//#define KEY_HOME 0x7f
//#define KEY_LWIN 0x8b
//#define KEY_RWIN 0x8c
//#define KEY_MENU 0x8d
//#define KEY_POWER 0xff
//#define KEY_SLEEP 0xff

#define CMD_SET_LED 0xed
#define CMD_ECHO 0xee
#define CMD_SCANCODE 0xf0
#define CMD_IDENTIFY 0xf2
#define CMD_TYPEMATIC 0xf3
#define CMD_ENABLE_SCANNING 0xf4
#define CMD_DISABLE_SCANNING 0xf5
#define CMD_SET_DEFAULT_PARAMS 0xf6
#define CMD_SET_KEYS_TM_AR 0xf7
#define CMD_SET_KEYS_M_R 0xf8
#define CMD_SET_KEYS_M 0xf9
#define CMD_SET_KEYS_TM_AR_M_R 0xfa
#define CMD_SET_KEY_TM_AR 0xfb
#define CMD_SET_KEY_M_R 0xfc
#define CMD_SET_KEY_M 0xfd
#define CMD_RESEND 0xfe
#define CMD_RESET 0xff

#define KEY_DETECT_ERROR 0x00 0xff
#define INTERNAL_BUFFER_OVERRUN 0x00 0xff
#define SELF_TEST_PASSED 0xaa
#define ACK 0xfa
#define SELF_TEST_FAILED 0xfc 0xfd
#define RESEND 0xfe

unsigned char read_kb(void);

#endif
