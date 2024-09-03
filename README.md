# Walker

### install
```
git clone https://github.com/Ztirom45/walker.git
```
follow the setup instructions

### setup
- rename ./wifimod/src/password_example.h to password.h

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
--new message-- 
data:<message>
--end of message--
```
- the arduino looks for `"--new message--"` to reconize a new message
- it reads the data in between of the `"data:"` and `"--end of message--"`
- **IMPORTANT:** do not use `"data:"` or `"--end of message--"` inside a message
- **IMPORTANT:** the `<message>` part can't longer than `MAX_COMMAND_LEN` (50 chars)

### the walker uses a protocol to move via mqtt (Work in Progress) 🖥️⟶ 🖥️:
- a command followed by parameters separeatet with a space and ends with a \n
- example: forward 10

### comand list (Work in Progress)⌨️
- [X] forward(speed) ⥣
- [X] leftMotor(speed) [⟲ X]
- [X] rightMotor(speed) [X ⟲]
- [ ] turn(speed, degree) ⟲ requires Gyro
- [ ] turn(speed) ⟲ +==right -==left
- [X] stop()
- [X] follow_wall()

### TODO:
- [ ] Gyro
- [ ] controller app
- [ ] maybe camera
- [ ] fix motor acceleration problem
- [ ] real support for commands which are looped (like follow_wall)
