%% Read data
% 76 secs. with 257 data per second
%MT9euler = importfileMT9euler('xsensMT9B/no_movement/MT9_euler_00007154_000.log', 1, 18273);
%MT9all = importfileMT9raw('xsensMT9B/no_movement/MT9_cal_00007154_000.log', 1, 18273);

% 76 secs. with 257 data per second (no movement)
MT9euler = importfileMT9euler('xsensMT9B/01_no_movement/MT9_euler_00007154_000.log', 1, 18148);
MT9all = importfileMT9raw('xsensMT9B/01_no_movement/MT9_cal_00007154_000.log', 1, 18148);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 19533);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 19533);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 19533);
my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 19533);
rawmagnetometers = importfile_raw_magnetometers('RESLT/raw_magnetometers.dat', 1, 19533);

% 82 secs. with 257 data per second (characterise yaw drift)
% MT9euler = importfileMT9euler('xsensMT9B/03_characterise_yaw_drift/MT9_euler_00007154_000.log', 2188, 20993);
% MT9all = importfileMT9raw('xsensMT9B/03_characterise_yaw_drift/MT9_cal_00007154_000.log', 2188, 20993);
% my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 21075);
% my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 21075);
% inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 21075);
% my_ddrift_yaw = importfile_my_roll_pitch_yaw('RESLT/ddrift_yaw.dat', 1, 21075);
% my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 21075);
% rawmagnetometers = importfile_raw_magnetometers('RESLT/raw_magnetometers.dat', 1, 21075);

% 17 mins. with 257 data per second (characterise yaw drift2)
MT9euler = importfileMT9euler('xsensMT9B/04_characterise_yaw_drift2/MT9_euler_00007154_000.log', 1, 266959);
MT9all = importfileMT9raw('xsensMT9B/04_characterise_yaw_drift2/MT9_cal_00007154_000.log', 1, 266959);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 273707);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 273707);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 273707);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('RESLT/ddrift_yaw.dat', 1, 273707);
my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 273707);
rawmagnetometers = importfile_raw_magnetometers('RESLT/raw_magnetometers.dat', 1, 273707);

% x secs. with 257 data per second (ellipse movement)
% MT9euler = importfileMT9euler('xsensMT9B/02_test_ellipse_movement/MT9_euler_00007154_000.log', 1, 20076);
% MT9all = importfileMT9raw('xsensMT9B/02_test_ellipse_movement/MT9_cal_00007154_000.log', 1, 20076);
% my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 26472);
% my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 26472);
% inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 26472);
% my_ddrift_yaw = importfile_my_roll_pitch_yaw('RESLT/ddrift_yaw.dat', 1, 26472);
% my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 26472);

% half hour with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/06_characterise_yaw_drift_0.5hrs/MT9_euler_00007154_001.log', 1, 524668);
MT9all = importfileMT9raw('xsensMT9B/06_characterise_yaw_drift_0.5hrs/MT9_cal_00007154_001.log', 1, 524668);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1, 527622);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 527622);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 527622);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('RESLT/ddrift_yaw.dat', 1, 527622);
my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 527622);

% 2 hours with 257 data per second
% MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 1808483);
% MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 1808483);
% my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('RESLT/roll_pitch_yaw.dat', 1816991);
% my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('RESLT/roll_pitch_yaw_from_acc.dat', 1, 1816991);
% inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('RESLT/inertial_accelerations.dat', 1, 1816991);
% my_ddrift_yaw = importfile_my_roll_pitch_yaw('RESLT/ddrift_yaw.dat', 1, 1816991);
% my_position = importfile_positionxsensMT9B('RESLT/position.dat', 1, 1816991);

%% Characterising drift
% 1 secs with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 251);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 251);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/01sec/roll_pitch_yaw.dat', 1702);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/01sec/roll_pitch_yaw_from_acc.dat', 1, 1702);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/01sec/inertial_accelerations.dat', 1, 1702);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/01sec/ddrift_yaw.dat', 1, 1702);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/01sec/position.dat', 1, 1702);

% 5 secs with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 1281);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 1281);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/05secs/roll_pitch_yaw.dat', 2730);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/05secs/roll_pitch_yaw_from_acc.dat', 1, 2730);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/05secs/inertial_accelerations.dat', 1, 2730);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/05secs/ddrift_yaw.dat', 1, 2730);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/05secs/position.dat', 1, 2730);

% 10 secs with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 2561);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 2561);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/10secs/roll_pitch_yaw.dat', 4015);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/10secs/roll_pitch_yaw_from_acc.dat', 1, 4015);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/10secs/inertial_accelerations.dat', 1, 4015);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/10secs/ddrift_yaw.dat', 1, 4015);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/10secs/position.dat', 1, 4015);

% 20 secs with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 5121);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 5121);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/20secs/roll_pitch_yaw.dat', 6585);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/20secs/roll_pitch_yaw_from_acc.dat', 1, 6585);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/20secs/inertial_accelerations.dat', 1, 6585);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/20secs/ddrift_yaw.dat', 1, 6585);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/20secs/position.dat', 1, 6585);

% 30 secs with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 7679);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 7679);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/30secs/roll_pitch_yaw.dat', 9155);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/30secs/roll_pitch_yaw_from_acc.dat', 1, 9155);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/30secs/inertial_accelerations.dat', 1, 9155);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/30secs/ddrift_yaw.dat', 1, 9155);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/30secs/position.dat', 1, 9155);

% 60 secs with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 15361);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 15361);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/60secs/roll_pitch_yaw.dat', 16865);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/60secs/roll_pitch_yaw_from_acc.dat', 1, 16865);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/60secs/inertial_accelerations.dat', 1, 16865);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/60secs/ddrift_yaw.dat', 1, 16865);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/60secs/position.dat', 1, 16865);

% 05 mins with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 76801);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 76801);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/05mins/roll_pitch_yaw.dat', 78545);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/05mins/roll_pitch_yaw_from_acc.dat', 1, 78545);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/05mins/inertial_accelerations.dat', 1, 78545);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/05mins/ddrift_yaw.dat', 1, 78545);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/05mins/position.dat', 1, 78545);

% 10 mins with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 153601);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 153601);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/10mins/roll_pitch_yaw.dat', 155645);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/10mins/roll_pitch_yaw_from_acc.dat', 1, 155645);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/10mins/inertial_accelerations.dat', 1, 155645);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/10mins/ddrift_yaw.dat', 1, 155645);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/10mins/position.dat', 1, 155645);

% 20 mins with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 307201);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 307201);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/20mins/roll_pitch_yaw.dat', 309845);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/20mins/roll_pitch_yaw_from_acc.dat', 1, 309845);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/20mins/inertial_accelerations.dat', 1, 309845);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/20mins/ddrift_yaw.dat', 1, 309845);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/20mins/position.dat', 1, 309845);

% 30 mins with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 460801);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 460801);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/30mins/roll_pitch_yaw.dat', 464045);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/30mins/roll_pitch_yaw_from_acc.dat', 1, 464045);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/30mins/inertial_accelerations.dat', 1, 464045);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/30mins/ddrift_yaw.dat', 1, 464045);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/30mins/position.dat', 1, 464045);

% 40 mins with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 614401);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 614401);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/40mins/roll_pitch_yaw.dat', 618245);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/40mins/roll_pitch_yaw_from_acc.dat', 1, 618245);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/40mins/inertial_accelerations.dat', 1, 618245);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/40mins/ddrift_yaw.dat', 1, 618245);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/40mins/position.dat', 1, 618245);

% 50 mins with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 768001);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 768001);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/50mins/roll_pitch_yaw.dat', 772445);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/50mins/roll_pitch_yaw_from_acc.dat', 1, 772445);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/50mins/inertial_accelerations.dat', 1, 772445);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/50mins/ddrift_yaw.dat', 1, 772445);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/50mins/position.dat', 1, 772445);

% 60 mins with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 921601);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 921601);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/60mins/roll_pitch_yaw.dat', 926645);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/60mins/roll_pitch_yaw_from_acc.dat', 1, 926645);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/60mins/inertial_accelerations.dat', 1, 926645);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/60mins/ddrift_yaw.dat', 1, 926645);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/60mins/position.dat', 1, 926645);

% 1 hour 15 mins with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 1152001);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 1152001);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/01hour15mins/roll_pitch_yaw.dat', 1157945);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/01hour15mins/roll_pitch_yaw_from_acc.dat', 1, 1157945);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/01hour15mins/inertial_accelerations.dat', 1, 1157945);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/01hour15mins/ddrift_yaw.dat', 1, 1157945);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/01hour15mins/position.dat', 1, 1157945);

% 1 hour 30 mins with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 1382401);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 1382401);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/01hour30mins/roll_pitch_yaw.dat', 1389245);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/01hour30mins/roll_pitch_yaw_from_acc.dat', 1, 1389245);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/01hour30mins/inertial_accelerations.dat', 1, 1389245);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/01hour30mins/ddrift_yaw.dat', 1, 1389245);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/01hour30mins/position.dat', 1, 1389245);

% 1 hour 45 mins with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 1612801);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 1612801);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/01hour45mins/roll_pitch_yaw.dat', 1620545);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/01hour45mins/roll_pitch_yaw_from_acc.dat', 1, 1620545);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/01hour45mins/inertial_accelerations.dat', 1, 1620545);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/01hour45mins/ddrift_yaw.dat', 1, 1620545);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/01hour45mins/position.dat', 1, 1620545);

% 2 hours with 257 data per second
MT9euler = importfileMT9euler('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log', 1, 1808483);
MT9all = importfileMT9raw('xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log', 1, 1808483);
my_roll_pitch_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/02hours/roll_pitch_yaw.dat', 1816964);
my_roll_pitch_yaw_from_acc = importfile_my_roll_pitch_yaw_from_acc('data_to_characterise_drift/02hours/roll_pitch_yaw_from_acc.dat', 1, 1816964);
inertial_acceleration = importfile_inertial_acceleration_xsensMT9B('data_to_characterise_drift/02hours/inertial_accelerations.dat', 1, 1816964);
my_ddrift_yaw = importfile_my_roll_pitch_yaw('data_to_characterise_drift/02hours/ddrift_yaw.dat', 1, 1816964);
my_position = importfile_positionxsensMT9B('data_to_characterise_drift/02hours/position.dat', 1, 1816964);

%% Euler angles
% Original vs processed roll
figure
%plot(MT9euler(:, 1), MT9euler(:, 2), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2)*180.0/pi, 'r')
plot(my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,2)*180.0/pi, 'g', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2)*180.0/pi, 'r', MT9euler(:, 1), MT9euler(:, 2), 'b')
title('Euler angle [roll]')
xlabel('Time (s)')
ylabel('\phi (degrees)')
legend('Angle from accelerometer', 'Gyroscope and accelerometer fusion', 'Solution', 'Location', 'NorthWest')

% Original vs processed pitch
figure
%plot(MT9euler(:, 1), MT9euler(:, 3), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3)*180.0/pi, 'r')
plot(my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,3)*180.0/pi, 'g', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3)*180.0/pi, 'r', MT9euler(:, 1), MT9euler(:, 3), 'b')
title('Euler angle [pitch]')
xlabel('Time(s)')
ylabel('\theta (degrees)')
legend('Angle from accelerometer', 'Gyroscope and accelerometer fusion', 'Solution', 'Location', 'NorthWest')

% Original vs processed rollacc_angles[2] = atan2(acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]));
figure
%plot(MT9euler(:, 1), MT9euler(:, 4), 'b', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r')
plot(my_roll_pitch_yaw_from_acc(:,1), my_roll_pitch_yaw_from_acc(:,4)*180.0/pi, 'g', my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4)*180.0/pi, 'r', MT9euler(:, 1), MT9euler(:, 4), 'b')
title('Euler angle [yaw]')
xlabel('Time(s)')
ylabel('\psi (degrees)')
legend('Angle from accelerometer', 'Gyroscope and accelerometer fusion', 'Solution', 'Location', 'NorthWest')

%% ddrift yaw
figure
plot(my_roll_pitch_yaw(:,1), my_ddrift_yaw(:, 4)*180.0/pi, 'b')
title('Rate of change yaw')
xlabel('Time(s)')
ylabel('ddrift (degrees)')
legend('ddrift yaw', 'Location', 'NorthWest')

%% Interpolate the obtained Euler angles
my_roll_interpolated = interp1(my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,2), MT9euler(:,1));
my_pitch_interpolated = interp1(my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,3), MT9euler(:,1));
my_yaw_interpolated = interp1(my_roll_pitch_yaw(:,1), my_roll_pitch_yaw(:,4), MT9euler(:,1));

my_diff_roll = abs(MT9euler(:,2) - my_roll_interpolated*180.0/pi);
my_diff_pitch = abs(MT9euler(:,3) - my_pitch_interpolated*180.0/pi);
my_diff_yaw = abs(MT9euler(:,4) - my_yaw_interpolated*180.0/pi);

figure
plot(MT9euler(:, 1), my_diff_roll, 'b')
title('Error \phi (roll)')
xlabel('Time(s)')
ylabel('\epsilon (degrees)')
legend('Error', 'Location', 'NorthWest')

figure
plot(MT9euler(:, 1), my_diff_pitch, 'b')
title('Error \theta (pitch)')
xlabel('Time(s)')
ylabel('\epsilon (degrees)')
legend('Error', 'Location', 'NorthWest')

figure
plot(MT9euler(:, 1), my_diff_yaw, 'b')
title('Error \psi (yaw)')
xlabel('Time(s)')
ylabel('\epsilon (degrees)')
legend('Error', 'Location', 'NorthWest')
hold

% Get the best fit
P = polyfit(MT9euler(:, 1), my_diff_yaw, 1)
%evaluate the polynomial to get some points
poly = polyval(P, MT9euler(:, 1));
plot(MT9euler(:, 1), poly, 'r')

%% Inertial acceleration
% figure
% plot(inertial_acceleration(:, 1), inertial_acceleration(:, 2), 'b')
% title('Inertial acceleration')
% xlabel('Time (s)')
% ylabel('x-acceleration')
% legend('Acceleration', 'Location', 'NorthWest')
% 
% figure
% plot(inertial_acceleration(:, 1), inertial_acceleration(:, 3), 'b')
% title('Inertial acceleration')
% xlabel('Time (s)')
% ylabel('y-acceleration')
% legend('Acceleration', 'Location', 'NorthWest')
% 
% figure
% plot(inertial_acceleration(:, 1), inertial_acceleration(:, 4), 'b')
% title('Inertial acceleration')
% xlabel('Time (s)')
% ylabel('z-acceleration')
% legend('Acceleration', 'Location', 'NorthWest')

%% Magnetometers
figure
plot(rawmagnetometers(:, 1), rawmagnetometers(:, 2), 'b')
title('Raw magnetometer [x]')
xlabel('Time(s)')
ylabel('data')
legend('Data', 'Location', 'NorthWest')

figure
plot(rawmagnetometers(:, 1), rawmagnetometers(:, 3), 'b')
title('Raw magnetometer [y]')
xlabel('Time(s)')
ylabel('data')
legend('Data', 'Location', 'NorthWest')

figure
plot(rawmagnetometers(:, 1), rawmagnetometers(:, 4), 'b')
title('Raw magnetometer [z]')
xlabel('Time(s)')
ylabel('data')
legend('Data', 'Location', 'NorthWest')

%% Position
% % Plot position
% figure
% plot(my_position(:, 2), my_position(:, 3), 'b')
% title('Trajectory')
% xlabel('x')
% ylabel('y')
% legend('Trajectory', 'Location', 'NorthWest')
