# Walker
<img src="https://github.com/Ztirom45/walker/blob/main/img/walker.png"/>

### install
```
git clone https://github.com/Ztirom45/walker.git
```
follow the setup instructions

### setup
- rename ./wifimod/src/password_example.h to password.h
- enter your wifi and mqtt server in this file

```
mv wifimod/src/password_example.h wifimod/src/password.h
```
- fill all constants with your wifi and server setup

### the walker is made out of 2 peaces
- the motor and sensor controll unit (A makeblock megapi, 📂[walker](./walker))
- a mqtt unit (a esp d1mini, 📂[wifimod](./wifimod))

### boath modules comunicate via uart 
- d1mini: Serial
- megapi:Serial3

### a protocol is used to transfare mqtt messages 🖥️⟶ 🖥️
- a message looks like this:
```
-m<message>-e
```
- the arduino looks for `"-m"` to reconize a new message
- it reads the data in between of the `message[2]` and `"-e"`
- **IMPORTANT:** do not use a `"-"` inside a message
- **IMPORTANT:** the `<message>` part can't longer than `MAX_COMMAND_LEN` (50 chars)

### the walker uses a protocol to move via mqtt (Work in Progress) 🖥️⟶ 🖥️:
- a command followed by parameters separeatet with a space and ends with a \n
- example: forward 10

### comand list (Work in Progress)⌨️
- [X] forward(speed) ⥣
- [X] left_motor(speed) [⟲ X]
- [X] right_motor(speed) [X ⟲]
- [ ] turn(speed, degree) ⟲ requires Gyro
- [X] turn(speed) ⟲ +==right -==left
- [X] stop()
- [X] follow_wall()
- [X] forward_stepwise() (walk with leg tracking, experimental: enable in sensors.hpp)
- [X] forward_gyro() (Work in progress)

### TODO:
- [X] Gyro
- [ ] controller app
- [ ] maybe camera
- [X] fix motor acceleration problem
- [X] real support for commands which are looped (like follow_wall)
