 while(true) {
         if(controller2.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
             end_mode = false;
         }

 
         if(end_mode == false) {//End Game Auto (PTO) Program
             // controller2.rumble("..");
             controller2.print(0, 0, "PTO SWITCH ON ");
 
             chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
             left_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
             right_motors.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
 
             subsystem::pneumatics.hold_wall_auto(false);
             pros::Task aim_ready_climb([&](){
                 subsystem::arm.pid_arm(Arm::position::CLIMB, 50, 5, 80);
             });
             subsystem::pneumatics.pto_auto(true);
             pros::delay(100);
             subsystem::pneumatics.ele_auto(true);
             subsystem::pneumatics.intake_auto(true);
 
 
             while (true) {
                 if(controller2.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) > 50) {
                     left_motors.move_voltage(12000);
                     right_motors.move_voltage(12000);                
                 }
                 else if (controller2.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) < -50) {
                     left_motors.move_voltage(-12000);
                     right_motors.move_voltage(-12000); 
                 }
                 else {
                     left_motors.brake();
                     right_motors.brake();
                 }
 
                 if(controller2.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
                     subsystem::pneumatics.ele_auto(true);
                 }
                 else if (controller2.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                     subsystem::pneumatics.ele_auto(false);
                 }
                 else {
 
                 }
 
                 if(controller2.get_digital(pros::E_CONTROLLER_DIGITAL_A) && controller2.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                     end_mode = true;
                     break;
                 }
             }
 
 
             // if(controller2.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
             //     left_motors.move_voltage(12000);
             //     right_motors.move_voltage(12000);                
             // }
             // else if (controller2.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
             //     left_motors.move_voltage(12000);
             //     right_motors.move_voltage(12000); 
             // }
             // else {
             //     left_motors.brake();
             //     right_motors.brake();
             // }
 
             // if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
             //     subsystem::pneumatics.ele_auto(true);
             // }
             // else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
             //     subsystem::pneumatics.ele_auto(false);
             // }
             // else {
 
             // }
         }
         else {
             subsystem::pneumatics.pto_auto(false);
             subsystem::pneumatics.ele_auto(false);
             subsystem::pneumatics.intake_auto(false);
             subsystem::pneumatics.hold_wall_auto(true);
             chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
             left_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
             right_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
             // controller2.rumble("..");
             controller2.print(0, 0, "PTO SWITCH OFF");
         }
 
         pros::delay(10);
     }
