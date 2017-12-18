typedef int signedPWM;
typedef enum {forward,backward,rotate_left,rotate_right,stop} action;

double c_dist_value;
bool c_dist_reqRead;
bool c_dist_reqWrite;
action c_act_value;
bool c_act_reqRead;
bool c_act_reqWrite;
signedPWM m1_speed_value;
bool m1_speed_reqRead;
bool m1_speed_reqWrite;
signedPWM m2_speed_value;
bool m2_speed_reqRead;
bool m2_speed_reqWrite;

int cmd_activated[7];
int cmd_activated_counter;
int cmd;

void setup() {
	c_dist_value = 0;
	c_dist_reqRead = 0;
	c_dist_reqWrite = 0;
	c_act_value = forward;
	c_act_reqRead = 0;
	c_act_reqWrite = 0;
	m1_speed_value = 0;
	m1_speed_reqRead = 0;
	m1_speed_reqWrite = 0;
	m2_speed_value = 0;
	m2_speed_reqRead = 0;
	m2_speed_reqWrite = 0;
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
}

void loop() {
	cmd_activated_counter = 0;
	if (!0 && !c_act_reqWrite) {
		cmd_activated[cmd_activated_counter] = 0;
		cmd_activated_counter ++;
	}
	if (!0 && !m1_speed_reqRead) {
		cmd_activated[cmd_activated_counter] = 1;
		cmd_activated_counter ++;
	}
	if (!0 && !m2_speed_reqRead) {
		cmd_activated[cmd_activated_counter] = 2;
		cmd_activated_counter ++;
	}
	if (!0 && c_act_reqWrite != m1_speed_reqWrite) {
		cmd_activated[cmd_activated_counter] = 3;
		cmd_activated_counter ++;
	}
	if (!0 || c_act_reqWrite != m1_speed_reqWrite && m1_speed_reqRead && m2_speed_reqRead != c_act_reqRead) {
		cmd_activated[cmd_activated_counter] = 4;
		cmd_activated_counter ++;
	}
	if (!0 && !c_dist_reqWrite) {
		cmd_activated[cmd_activated_counter] = 5;
		cmd_activated_counter ++;
	}
	if (!0 || !m2_speed_reqRead && m2_speed_reqRead && m2_speed_reqWrite && !0 || !c_dist_reqWrite && c_dist_reqRead && !0 || c_act_reqWrite != m1_speed_reqWrite || m1_speed_reqRead && m2_speed_reqRead != c_act_reqRead && c_act_reqRead && c_act_reqWrite && !0 || !m1_speed_reqRead && m1_speed_reqRead && m1_speed_reqWrite && !0 || !c_act_reqWrite && c_act_reqRead) {
		cmd_activated[cmd_activated_counter] = 6;
		cmd_activated_counter ++;
	}
	cmd = cmd_activated[random(cmd_activated_counter)];
	if (cmd == 0) {
		c_act_reqWrite = 1;
	}
	if (cmd == 1) {
		m1_speed_reqRead = 1;
	}
	if (cmd == 2) {
		m2_speed_reqRead = 1;
	}
	if (cmd == 3) {
		m1_speed_reqWrite = c_act_reqWrite;
		m2_speed_reqWrite = c_act_reqWrite;
	}
	if (cmd == 4) {
		c_act_reqRead = m1_speed_reqRead && m2_speed_reqRead;
	}
	if (cmd == 5) {
		c_dist_reqWrite = 1;
	}
	if (cmd == 6) {
		c_dist_reqWrite = 0;
		c_dist_reqRead = 0;
		c_act_value = stop;
		c_act_reqWrite = 0;
		c_act_reqRead = 0;
		if (c_act_value == forward) {
			m1_speed_value = 80;
			assert (m1_speed_value >= -1023 && m1_speed_value <= 1023);
			m2_speed_value = 80;
			assert (m2_speed_value >= -1023 && m2_speed_value <= 1023);
		} else {
			if (c_act_value == backward) {
			
			} else {
				if (c_act_value == stop) {
					m1_speed_value = 0;
					assert (m1_speed_value >= -1023 && m1_speed_value <= 1023);
					m2_speed_value = 0;
					assert (m2_speed_value >= -1023 && m2_speed_value <= 1023);
				}
			}
		}
		m1_speed_reqWrite = 0;
		m1_speed_reqRead = 0;
		if (m1_speed_value > 0) {
			digitalWrite(8, 1);
			analogWrite(9, m1_speed_value);
		} else {
			digitalWrite(8, 0);
			analogWrite(9, -m1_speed_value);
		}
		m2_speed_reqWrite = 0;
		m2_speed_reqRead = 0;
		if (m2_speed_value > 0) {
			digitalWrite(11, 1);
			analogWrite(10, m2_speed_value);
		} else {
			digitalWrite(11, 0);
			analogWrite(10, -m2_speed_value);
		}
	}
}
