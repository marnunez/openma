#include <cxxtest/TestDrive.h>

#include "plugingaitTest_def.h"
#include "tdd_file_path.h"

CXXTEST_SUITE(PluginGaitTest)
{
  CXXTEST_TEST(calibrateLeftFullBodyOneFrame)
  {
    ma::body::PluginGait helper(ma::body::Region::Full, ma::body::Side::Left);
    helper.setMarkerDiameter(16.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(940.0); // mm
    helper.setLeftKneeWidth(110.0); // mm
    helper.setLeftAnkleWidth(70.0); // mm
    helper.setRightLegLength(940.0); // mm (Because both leg length are needed)
    
    ma::Node root("root");
    generate_static_trial_oneframe(&root);
    helper.calibrate(&root, nullptr);
    
    TS_ASSERT_DELTA(helper.interAsisDistance(), 228.693, 5e-4);
    TS_ASSERT_DELTA(helper.property("interAsisDistance").cast<double>(), 228.693, 5e-4);
    TS_ASSERT_DELTA(helper.leftAsisTrochanterAPDistance(), 72.512, 5e-4);
    TS_ASSERT_DELTA(helper.property("leftAsisTrochanterAPDistance").cast<double>(), 72.512, 5e-4);
    TS_ASSERT_DELTA(helper.headOffset(), 0.0945073, 1e-4);
    TS_ASSERT_DELTA(helper.property("headOffset").cast<double>(), 0.0945073, 1e-4);
    TS_ASSERT_DELTA(helper.leftStaticPlantarFlexionOffset(), 0.197172, 1e-4);
    TS_ASSERT_DELTA(helper.property("leftStaticPlantarFlexionOffset").cast<double>(), 0.197172, 1e-4);
    TS_ASSERT_DELTA(helper.leftStaticRotationOffset(), 0.0164273, 1e-4);
    TS_ASSERT_DELTA(helper.property("leftStaticRotationOffset").cast<double>(), 0.0164273, 1e-4);
  };
  
  CXXTEST_TEST(calibrateRightFullBodyOneFrame)
  {
    ma::body::PluginGait helper(ma::body::Region::Full, ma::body::Side::Right);
    helper.setMarkerDiameter(16.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(940.0); // mm
    helper.setRightKneeWidth(120.0); // mm
    helper.setRightAnkleWidth(70.0); // mm
    helper.setLeftLegLength(940.0); // mm (Because both leg length are needed)
    
    ma::Node root("root");
    generate_static_trial_oneframe(&root);
    helper.calibrate(&root, nullptr);
    
    TS_ASSERT_DELTA(helper.interAsisDistance(), 228.693, 5e-4);
    TS_ASSERT_DELTA(helper.property("interAsisDistance").cast<double>(), 228.693, 5e-4);
    TS_ASSERT_DELTA(helper.rightAsisTrochanterAPDistance(), 72.512, 5e-4);
    TS_ASSERT_DELTA(helper.property("rightAsisTrochanterAPDistance").cast<double>(), 72.512, 5e-4);
    TS_ASSERT_DELTA(helper.headOffset(), 0.0945073, 1e-4);
    TS_ASSERT_DELTA(helper.property("headOffset").cast<double>(), 0.0945073, 1e-4);
    TS_ASSERT_DELTA(helper.rightStaticPlantarFlexionOffset(), 0.208874, 1e-4);
    TS_ASSERT_DELTA(helper.property("rightStaticPlantarFlexionOffset").cast<double>(), 0.208874, 1e-4);
    TS_ASSERT_DELTA(helper.rightStaticRotationOffset(), -0.0179406, 1e-4);
    TS_ASSERT_DELTA(helper.property("rightStaticRotationOffset").cast<double>(), -0.0179406, 1e-4);
  };
  
  CXXTEST_TEST(calibrateBothFullBodyOneFrame)
  {
    ma::body::PluginGait helper(ma::body::Region::Full, ma::body::Side::Both);
    helper.setMarkerDiameter(16.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(940.0); // mm
    helper.setLeftKneeWidth(110.0); // mm
    helper.setLeftAnkleWidth(70.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(940.0); // mm
    helper.setRightKneeWidth(120.0); // mm
    helper.setRightAnkleWidth(70.0); // mm
    
    ma::Node root("root");
    generate_static_trial_oneframe(&root);
    helper.calibrate(&root, nullptr);
    
    TS_ASSERT_DELTA(helper.interAsisDistance(), 228.693, 5e-4);
    TS_ASSERT_DELTA(helper.property("interAsisDistance").cast<double>(), 228.693, 5e-4);
    TS_ASSERT_DELTA(helper.headOffset(), 0.0945073, 1e-4);
    TS_ASSERT_DELTA(helper.property("headOffset").cast<double>(), 0.0945073, 1e-4);
    
    TS_ASSERT_DELTA(helper.leftAsisTrochanterAPDistance(), 72.512, 5e-4);
    TS_ASSERT_DELTA(helper.property("leftAsisTrochanterAPDistance").cast<double>(), 72.512, 5e-4);
    TS_ASSERT_DELTA(helper.leftStaticPlantarFlexionOffset(), 0.197172, 1e-4);
    TS_ASSERT_DELTA(helper.property("leftStaticPlantarFlexionOffset").cast<double>(), 0.197172, 1e-4);
    TS_ASSERT_DELTA(helper.leftStaticRotationOffset(), 0.0164273, 1e-4);
    TS_ASSERT_DELTA(helper.property("leftStaticRotationOffset").cast<double>(), 0.0164273, 1e-4);
    
    TS_ASSERT_DELTA(helper.rightAsisTrochanterAPDistance(), 72.512, 5e-4);
    TS_ASSERT_DELTA(helper.property("rightAsisTrochanterAPDistance").cast<double>(), 72.512, 5e-4);
    TS_ASSERT_DELTA(helper.rightStaticPlantarFlexionOffset(), 0.208874, 1e-4);
    TS_ASSERT_DELTA(helper.property("rightStaticPlantarFlexionOffset").cast<double>(), 0.208874, 1e-4);
    TS_ASSERT_DELTA(helper.rightStaticRotationOffset(), -0.0179406, 1e-4);
    TS_ASSERT_DELTA(helper.property("rightStaticRotationOffset").cast<double>(), -0.0179406, 1e-4);
  };
  
  CXXTEST_TEST(calibrateBothUpperBodyFullFrames)
  {
    ma::body::PluginGait helper(ma::body::Region::Upper, ma::body::Side::Both);
    
    ma::Node root("root");
    generate_trial_from_file(&root, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration-FlatFoot-Full.c3d"));
    TS_ASSERT_EQUALS(root.children().size(),1u);
    helper.calibrate(&root, nullptr);
    
    TS_ASSERT_EQUALS(helper.interAsisDistance(), 0.0);
    TS_ASSERT_DELTA(helper.headOffset(), 0.353677, 1e-4);
    TS_ASSERT_EQUALS(helper.leftAsisTrochanterAPDistance(), 0.0);
    TS_ASSERT_EQUALS(helper.leftStaticPlantarFlexionOffset(), 0.0);
    TS_ASSERT_EQUALS(helper.leftStaticRotationOffset(), 0.0);
    TS_ASSERT_EQUALS(helper.rightAsisTrochanterAPDistance(), 0.0);
    TS_ASSERT_EQUALS(helper.rightStaticPlantarFlexionOffset(), 0.0);
    TS_ASSERT_EQUALS(helper.rightStaticRotationOffset(), 0.0);
  };

  CXXTEST_TEST(calibrateBothLowerBodyFullFrames)
  {
    ma::body::PluginGait helper(ma::body::Region::Lower, ma::body::Side::Both);
    helper.setMarkerDiameter(16.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(800.0); // mm
    helper.setLeftKneeWidth(105.0); // mm
    helper.setLeftAnkleWidth(55.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(800.0); // mm
    helper.setRightKneeWidth(105.0); // mm
    helper.setRightAnkleWidth(55.0); // mm
    
    ma::Node root("root");
    generate_trial_from_file(&root, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration-FlatFoot-Full.c3d"));
    TS_ASSERT_EQUALS(root.children().size(),1u);
    helper.calibrate(&root, nullptr);
    
    TS_ASSERT_DELTA(helper.interAsisDistance(), 199.902, 5e-4);
    TS_ASSERT_EQUALS(helper.headOffset(), 0.0);
    TS_ASSERT_DELTA(helper.leftAsisTrochanterAPDistance(), 54.48, 5e-4);
    TS_ASSERT_DELTA(helper.leftStaticPlantarFlexionOffset(), 0.115969, 1e-4);
    TS_ASSERT_DELTA(helper.leftStaticRotationOffset(), 0.00446829, 1e-4);
    TS_ASSERT_DELTA(helper.rightAsisTrochanterAPDistance(), 54.48, 5e-4);
    TS_ASSERT_DELTA(helper.rightStaticPlantarFlexionOffset(), 0.162755, 1e-4);
    TS_ASSERT_DELTA(helper.rightStaticRotationOffset(), -0.0163829, 1e-4);
  };

  CXXTEST_TEST(calibrateBothFullBodyFullFrames)
  {
    ma::body::PluginGait helper(ma::body::Region::Full, ma::body::Side::Both);
    helper.setMarkerDiameter(16.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(800.0); // mm
    helper.setLeftKneeWidth(105.0); // mm
    helper.setLeftAnkleWidth(55.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(800.0); // mm
    helper.setRightKneeWidth(105.0); // mm
    helper.setRightAnkleWidth(55.0); // mm
    
    ma::Node root("root");
    generate_trial_from_file(&root, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration-FlatFoot-Full.c3d"));
    TS_ASSERT_EQUALS(root.children().size(),1u);
    helper.calibrate(&root, nullptr);
    
    TS_ASSERT_DELTA(helper.interAsisDistance(), 199.902, 5e-4);
    TS_ASSERT_DELTA(helper.headOffset(), 0.353677, 1e-4);
    TS_ASSERT_DELTA(helper.leftAsisTrochanterAPDistance(), 54.48, 5e-4);
    TS_ASSERT_DELTA(helper.leftStaticPlantarFlexionOffset(), 0.115969, 1e-4);
    TS_ASSERT_DELTA(helper.leftStaticRotationOffset(), 0.00446829, 1e-4);
    TS_ASSERT_DELTA(helper.rightAsisTrochanterAPDistance(), 54.48, 5e-4);
    TS_ASSERT_DELTA(helper.rightStaticPlantarFlexionOffset(), 0.162755, 1e-4);
    TS_ASSERT_DELTA(helper.rightStaticRotationOffset(), -0.0163829, 1e-4);
  };
  
  CXXTEST_TEST(calibrateBothFullBodyHoleFrames)
  {
    ma::body::PluginGait helper(ma::body::Region::Full, ma::body::Side::Both);
    helper.setMarkerDiameter(16.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(940.0); // mm
    helper.setLeftKneeWidth(110.0); // mm
    helper.setLeftAnkleWidth(70.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(940.0); // mm
    helper.setRightKneeWidth(120.0); // mm
    helper.setRightAnkleWidth(70.0); // mm
    
    ma::Node root("root");
    generate_trial_from_file(&root, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration-FlatFoot-Hole.c3d"));
    TS_ASSERT_EQUALS(root.children().size(),1u);
    helper.calibrate(&root, nullptr);
    
    TS_ASSERT_DELTA(helper.interAsisDistance(), 227.043, 5e-4);
    TS_ASSERT_DELTA(helper.headOffset(), 0.123762, 1e-4);
    TS_ASSERT_DELTA(helper.leftAsisTrochanterAPDistance(), 72.512, 5e-4);
    TS_ASSERT_DELTA(helper.leftStaticPlantarFlexionOffset(), 0.197419, 1e-4);
    TS_ASSERT_DELTA(helper.leftStaticRotationOffset(), 0.0178294, 1e-4);
    TS_ASSERT_DELTA(helper.rightAsisTrochanterAPDistance(), 72.512, 5e-4);
    TS_ASSERT_DELTA(helper.rightStaticPlantarFlexionOffset(), 0.209483, 1e-4);
    TS_ASSERT_DELTA(helper.rightStaticRotationOffset(), -0.0183813, 1e-4);
  };
  
  CXXTEST_TEST(calibrate2BothFullBodyNoOption)
  {
    ma::body::PluginGait helper(ma::body::Region::Lower, ma::body::Side::Both);
    helper.setMarkerDiameter(14.0); // mm
    helper.setInterAsisDistance(255.0); // mm
    helper.setLeftLegLength(905.0); // mm
    helper.setLeftKneeWidth(105.0); // mm
    helper.setLeftAnkleWidth(75.0); // mm
    helper.setRightLegLength(905.0); // mm
    helper.setRightKneeWidth(105.0); // mm
    helper.setRightAnkleWidth(75.0); // mm
    
    ma::Node root("root");
    generate_trial_from_file(&root, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration2-NoOption.c3d"));
    TS_ASSERT_EQUALS(root.children().size(),1u);
    helper.calibrate(&root, nullptr);

    TS_ASSERT_DELTA(helper.interAsisDistance(), 255.0, 1e-15);
    TS_ASSERT_DELTA(helper.leftAsisTrochanterAPDistance(), 68.004, 5e-3);
    TS_ASSERT_DELTA(helper.leftStaticPlantarFlexionOffset(), 0.202148, 1e-4);
    TS_ASSERT_DELTA(helper.leftStaticRotationOffset(), 0.0270116, 1e-4);
    TS_ASSERT_DELTA(helper.rightAsisTrochanterAPDistance(), 68.004, 5e-3);
    TS_ASSERT_DELTA(helper.rightStaticPlantarFlexionOffset(), 0.233063, 1e-4);
    TS_ASSERT_DELTA(helper.rightStaticRotationOffset(), 0.00807751, 1e-4);
  };
  
  CXXTEST_TEST(calibrate3BothLowerBodyFF)
  {
    ma::body::PluginGait helper(ma::body::Region::Lower, ma::body::Side::Both);
    helper.setMarkerDiameter(14.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(920.0); // mm
    helper.setLeftKneeWidth(102.0); // mm
    helper.setLeftAnkleWidth(70.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(920.0); // mm
    helper.setRightKneeWidth(102.0); // mm
    helper.setRightAnkleWidth(70.0); // mm
    
    ma::Node root("root");
    generate_trial_from_file(&root, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration3_FF.c3d"));
    TS_ASSERT_EQUALS(root.children().size(),1u);
    helper.calibrate(&root, nullptr);

    TS_ASSERT_DELTA(helper.interAsisDistance(), 245.244, 5e-3);
    TS_ASSERT_DELTA(helper.leftAsisTrochanterAPDistance(), 69.936, 5e-3);
    TS_ASSERT_DELTA(helper.leftStaticPlantarFlexionOffset(), 0.15719, 1e-4);
    TS_ASSERT_DELTA(helper.leftStaticRotationOffset(), -0.0888886, 1e-4);
    TS_ASSERT_DELTA(helper.rightAsisTrochanterAPDistance(), 69.936, 5e-3);
    TS_ASSERT_DELTA(helper.rightStaticPlantarFlexionOffset(), 0.186005, 1e-4);
    TS_ASSERT_DELTA(helper.rightStaticRotationOffset(), -0.0166437, 1e-4);
  };
  
  CXXTEST_TEST(calibrate3BothLowerBodyFF_N18)
  {
    ma::body::PluginGait helper(ma::body::Region::Lower, ma::body::Side::Both);
    helper.setMarkerDiameter(14.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(920.0); // mm
    helper.setLeftKneeWidth(102.0); // mm
    helper.setLeftAnkleWidth(70.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(920.0); // mm
    helper.setRightKneeWidth(102.0); // mm
    helper.setRightAnkleWidth(70.0); // mm
    
    ma::Node root("root");
    generate_trial_from_file(&root, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration3_FF_N18.c3d"));
    TS_ASSERT_EQUALS(root.children().size(),1u);
    helper.calibrate(&root, nullptr);

    TS_ASSERT_DELTA(helper.interAsisDistance(), 245.32, 5e-3);
    TS_ASSERT_DELTA(helper.leftStaticPlantarFlexionOffset(), 0.157482, 1e-4);
    TS_ASSERT_DELTA(helper.leftStaticRotationOffset(), -0.0890265, 1e-4);
    TS_ASSERT_DELTA(helper.rightStaticPlantarFlexionOffset(), 0.18605, 1e-4);
    TS_ASSERT_DELTA(helper.rightStaticRotationOffset(), -0.0165357, 1e-4);
  };
  
  CXXTEST_TEST(calibrate3BothLowerBodynoFF)
  {
    ma::body::PluginGait helper(ma::body::Region::Lower, ma::body::Side::Both);
    helper.setMarkerDiameter(14.0); // mm
    helper.setLeftLegLength(920.0); // mm
    helper.setLeftKneeWidth(102.0); // mm
    helper.setLeftAnkleWidth(70.0); // mm
    helper.setRightLegLength(920.0); // mm
    helper.setRightKneeWidth(102.0); // mm
    helper.setRightAnkleWidth(70.0); // mm
    
    ma::Node root("root");
    generate_trial_from_file(&root, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration3_noFF.c3d"));
    TS_ASSERT_EQUALS(root.children().size(),1u);
    helper.calibrate(&root, nullptr);

    // TS_ASSERT_DELTA(helper.interAsisDistance(), 245.236, 5e-3); // Should be 245.244 like Calibrate3BothLowerBodyFF but Nexus computed a length of 245.236...
    TS_ASSERT_DELTA(helper.leftAsisTrochanterAPDistance(), 69.936, 5e-3);
    TS_ASSERT_DELTA(helper.leftStaticPlantarFlexionOffset(), 0.146773, 1e-4);
    TS_ASSERT_DELTA(helper.leftStaticRotationOffset(), -0.0883149, 1e-4);
    TS_ASSERT_DELTA(helper.rightAsisTrochanterAPDistance(), 69.936, 5e-3);
    TS_ASSERT_DELTA(helper.rightStaticPlantarFlexionOffset(), 0.128716, 1e-4);
    TS_ASSERT_DELTA(helper.rightStaticRotationOffset(), -0.00978336, 1e-4);
  };
  
  // ----------------------------------------------------------------------- //
  
  CXXTEST_TEST(reconstructBothLowerBodyOneFrame)
  {
    ma::body::PluginGait helper(ma::body::Region::Lower, ma::body::Side::Both);
    helper.setMarkerDiameter(16.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(940.0); // mm
    helper.setLeftKneeWidth(110.0); // mm
    helper.setLeftAnkleWidth(70.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(940.0); // mm
    helper.setRightKneeWidth(120.0); // mm
    helper.setRightAnkleWidth(70.0); // mm
    
    ma::Node rootCalibration("rootCalibration"), rootDynamic("rootDynamic"), rootModel("rootModel");
    generate_trial_from_file(&rootCalibration, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration-FlatFoot-One.c3d"));
    TS_ASSERT(helper.calibrate(&rootCalibration, nullptr));
    generate_trial_from_file(&rootDynamic, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Motion-FlatFoot-One.c3d"));
    TS_ASSERT(helper.reconstruct(&rootModel, &rootDynamic));
    
    auto trial = rootDynamic.findChild<ma::Trial*>();
    compare_segment_motion(trial, "Pelvis.SCS", {"PELO","PELA","PELL","PELP"}, {5e-4});
    compare_segment_motion(trial, "R.Thigh.SCS", {"RFEO","RFEA","RFEL","RFEP"}, {5e-4});
    compare_segment_motion(trial, "L.Thigh.SCS", {"LFEO","LFEA","LFEL","LFEP"}, {5e-4});
    compare_segment_motion(trial, "R.Shank.SCS", {"RTIO","RTIA","RTIL","RTIP"}, {5e-4});
    compare_segment_motion(trial, "L.Shank.SCS", {"LTIO","LTIA","LTIL","LTIP"}, {5e-4});
    compare_segment_motion(trial, "R.Foot.SCS", {"RFOO","RFOA","RFOL","RFOP"}, {1e4}); // 1e4 : Not the same ohelperin
    compare_segment_motion(trial, "L.Foot.SCS", {"LFOO","LFOA","LFOL","LFOP"}, {1e4}); // 1e4 : Not the same ohelperin
  };
  
  CXXTEST_TEST(reconstructBothUpperBodyOneFrame)
  {
    ma::body::PluginGait helper(ma::body::Region::Upper, ma::body::Side::Both);
    helper.setMarkerDiameter(16.0); // mm
    helper.setLeftShoulderOffset(50.0); // mm
    helper.setRightShoulderOffset(50.0); // mm
    helper.setLeftElbowWidth(80.0); // mm
    helper.setRightElbowWidth(80.0); // mm
    helper.setLeftWristWidth(40.0); // mm
    helper.setRightWristWidth(40.0); // mm
    helper.setLeftHandThickness(30.0); // mm
    helper.setRightHandThickness(30.0); // mm
    
    ma::Node rootCalibration("rootCalibration"), rootDynamic("rootDynamic"), rootModel("rootModel");
    generate_trial_from_file(&rootCalibration, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration-FlatFoot-One.c3d"));
    TS_ASSERT(helper.calibrate(&rootCalibration, nullptr));
    generate_trial_from_file(&rootDynamic, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Motion-FlatFoot-One.c3d"));
    TS_ASSERT(helper.reconstruct(&rootModel, &rootDynamic));
    
    auto trial = rootDynamic.findChild<ma::Trial*>();
    compare_segment_motion(trial, "Head.SCS", {"HEDO","HEDA","HEDL","HEDP"}, {1e4}); // 1e4 : Not the same ohelperin
    compare_segment_motion(trial, "Torso.SCS", {"TRXO","TRXA","TRXL","TRXP"}, {5e-4});
    compare_segment_motion(trial, "L.Clavicle.SCS", {"LCLO","LCLA","LCLL","LCLP"}, {5e-4});
    compare_segment_motion(trial, "R.Clavicle.SCS", {"RCLO","RCLA","RCLL","RCLP"}, {5e-4});
    compare_segment_motion(trial, "L.Arm.SCS", {"LHUO","LHUA","LHUL","LHUP"}, {5e-4});
    compare_segment_motion(trial, "R.Arm.SCS", {"RHUO","RHUA","RHUL","RHUP"}, {5e-4});
    compare_segment_motion(trial, "L.Forearm.SCS", {"LRAO","LRAA","LRAL","LRAP"}, {5e-4});
    compare_segment_motion(trial, "R.Forearm.SCS", {"RRAO","RRAA","RRAL","RRAP"}, {5e-4});
    compare_segment_motion(trial, "L.Hand.SCS", {"LHNO","LHNA","LHNL","LHNP"}, {5e-4});
    compare_segment_motion(trial, "R.Hand.SCS", {"RHNO","RHNA","RHNL","RHNP"}, {5e-4});
  };
  
  CXXTEST_TEST(reconstructBothLowerBodyHoleFrames)
  {
    ma::body::PluginGait helper(ma::body::Region::Lower, ma::body::Side::Both);
    helper.setMarkerDiameter(16.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(940.0); // mm
    helper.setLeftKneeWidth(110.0); // mm
    helper.setLeftAnkleWidth(70.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(940.0); // mm
    helper.setRightKneeWidth(120.0); // mm
    helper.setRightAnkleWidth(70.0); // mm
    
    ma::Node rootCalibration("rootCalibration"), rootDynamic("rootDynamic"), rootModel("rootModel");
    generate_trial_from_file(&rootCalibration, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration-FlatFoot-Hole.c3d"));
    TS_ASSERT(helper.calibrate(&rootCalibration, nullptr));
    generate_trial_from_file(&rootDynamic, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Motion-FlatFoot-Hole.c3d"));
    TS_ASSERT(helper.reconstruct(&rootModel, &rootDynamic));
    
    auto trial = rootDynamic.findChild<ma::Trial*>();
    compare_segment_motion(trial, "Pelvis.SCS", {"PELO","PELA","PELL","PELP"}, {1e-3});
    compare_segment_motion(trial, "R.Thigh.SCS", {"RFEO","RFEA","RFEL","RFEP"}, {75e-5});
    compare_segment_motion(trial, "L.Thigh.SCS", {"LFEO","LFEA","LFEL","LFEP"}, {1e-3});
    compare_segment_motion(trial, "R.Shank.SCS", {"RTIO","RTIA","RTIL","RTIP"}, {7e-4});
    compare_segment_motion(trial, "L.Shank.SCS", {"LTIO","LTIA","LTIL","LTIP"}, {1e-3});
    compare_segment_motion(trial, "R.Foot.SCS", {"RFOO","RFOA","RFOL","RFOP"}, {1e4}); // 1e4 : Not the same ohelperin
    compare_segment_motion(trial, "L.Foot.SCS", {"LFOO","LFOA","LFOL","LFOP"}, {1e4}); // 1e4 : Not the same ohelperin
  };
  
  CXXTEST_TEST(reconstructBothUpperBodyHoleFrames)
  {
    ma::body::PluginGait helper(ma::body::Region::Upper, ma::body::Side::Both);
    helper.setMarkerDiameter(16.0); // mm
    helper.setLeftShoulderOffset(50.0); // mm
    helper.setRightShoulderOffset(50.0); // mm
    helper.setLeftElbowWidth(80.0); // mm
    helper.setRightElbowWidth(80.0); // mm
    helper.setLeftWristWidth(40.0); // mm
    helper.setRightWristWidth(40.0); // mm
    helper.setLeftHandThickness(30.0); // mm
    helper.setRightHandThickness(30.0); // mm
    
    ma::Node rootCalibration("rootCalibration"), rootDynamic("rootDynamic"), rootModel("rootModel");
    generate_trial_from_file(&rootCalibration, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration-FlatFoot-Hole.c3d"));
    TS_ASSERT(helper.calibrate(&rootCalibration, nullptr));
    generate_trial_from_file(&rootDynamic, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Motion-FlatFoot-Hole.c3d"));
    TS_ASSERT(helper.reconstruct(&rootModel, &rootDynamic));
    
    auto trial = rootDynamic.findChild<ma::Trial*>();
    // NOTE: The accuracy is not the same than for the other unit tests. The reason is not known
    compare_segment_motion(trial, "Head.SCS", {"HEDO","HEDA","HEDL","HEDP"}, {1e4}); // 1e4 : Not the same ohelperin
    compare_segment_motion(trial, "Torso.SCS", {"TRXO","TRXA","TRXL","TRXP"}, {1e-3});
    compare_segment_motion(trial, "L.Clavicle.SCS", {"LCLO","LCLA","LCLL","LCLP"}, {1e-3});
    compare_segment_motion(trial, "R.Clavicle.SCS", {"RCLO","RCLA","RCLL","RCLP"}, {1e-3});
    compare_segment_motion(trial, "L.Arm.SCS", {"LHUO","LHUA","LHUL","LHUP"}, {1e-3});
    compare_segment_motion(trial, "R.Arm.SCS", {"RHUO","RHUA","RHUL","RHUP"}, {1e-3});
    compare_segment_motion(trial, "L.Forearm.SCS", {"LRAO","LRAA","LRAL","LRAP"}, {1e-3});
    compare_segment_motion(trial, "R.Forearm.SCS", {"RRAO","RRAA","RRAL","RRAP"}, {1e-3});
    compare_segment_motion(trial, "L.Hand.SCS", {"LHNO","LHNA","LHNL","LHNP"}, {1e-3});
    compare_segment_motion(trial, "R.Hand.SCS", {"RHNO","RHNA","RHNL","RHNP"}, {15e-4});
  };
  
  CXXTEST_TEST(reconstructBothFullBodyFullFrames)
  {
    ma::body::PluginGait helper(ma::body::Region::Full, ma::body::Side::Both);
    helper.setMarkerDiameter(16.0); // mm
    helper.setLeftShoulderOffset(50.0); // mm
    helper.setRightShoulderOffset(50.0); // mm
    helper.setLeftElbowWidth(80.0); // mm
    helper.setRightElbowWidth(80.0); // mm
    helper.setLeftWristWidth(40.0); // mm
    helper.setRightWristWidth(40.0); // mm
    helper.setLeftHandThickness(30.0); // mm
    helper.setRightHandThickness(30.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(800.0); // mm
    helper.setLeftKneeWidth(105.0); // mm
    helper.setLeftAnkleWidth(55.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(800.0); // mm
    helper.setRightKneeWidth(105.0); // mm
    helper.setRightAnkleWidth(55.0); // mm
    
    ma::Node rootCalibration("rootCalibration"), rootDynamic("rootDynamic"), rootModel("rootModel");
    generate_trial_from_file(&rootCalibration, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration-FlatFoot-Full.c3d"));
    TS_ASSERT(helper.calibrate(&rootCalibration, nullptr));
    generate_trial_from_file(&rootDynamic, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Motion-FlatFoot-Full.c3d"));
    TS_ASSERT(helper.reconstruct(&rootModel, &rootDynamic));
    
    auto trial = rootDynamic.findChild<ma::Trial*>();
    // NOTE: The accuracy is not the same than for the other unit tests. The reason is not known
    compare_segment_motion(trial, "Head.SCS", {"HEDO","HEDA","HEDL","HEDP"}, {1e4}); // 1e4 : Not the same ohelperin
    compare_segment_motion(trial, "Torso.SCS", {"TRXO","TRXA","TRXL","TRXP"}, {5e-4});
    compare_segment_motion(trial, "L.Clavicle.SCS", {"LCLO","LCLA","LCLL","LCLP"}, {5e-4});
    compare_segment_motion(trial, "R.Clavicle.SCS", {"RCLO","RCLA","RCLL","RCLP"}, {5e-4});
    compare_segment_motion(trial, "L.Arm.SCS", {"LHUO","LHUA","LHUL","LHUP"}, {5e-4});
    compare_segment_motion(trial, "R.Arm.SCS", {"RHUO","RHUA","RHUL","RHUP"}, {6e-4});
    compare_segment_motion(trial, "L.Forearm.SCS", {"LRAO","LRAA","LRAL","LRAP"}, {5e-4});
    compare_segment_motion(trial, "R.Forearm.SCS", {"RRAO","RRAA","RRAL","RRAP"}, {5e-4});
    compare_segment_motion(trial, "L.Hand.SCS", {"LHNO","LHNA","LHNL","LHNP"}, {6e-4});
    compare_segment_motion(trial, "R.Hand.SCS", {"RHNO","RHNA","RHNL","RHNP"}, {5e-4});
    compare_segment_motion(trial, "Pelvis.SCS", {"PELO","PELA","PELL","PELP"}, {5e-4});
    compare_segment_motion(trial, "R.Thigh.SCS", {"RFEO","RFEA","RFEL","RFEP"}, {5e-4});
    compare_segment_motion(trial, "L.Thigh.SCS", {"LFEO","LFEA","LFEL","LFEP"}, {5e-4});
    compare_segment_motion(trial, "R.Shank.SCS", {"RTIO","RTIA","RTIL","RTIP"}, {5e-4});
    compare_segment_motion(trial, "L.Shank.SCS", {"LTIO","LTIA","LTIL","LTIP"}, {6e-4});
    compare_segment_motion(trial, "R.Foot.SCS", {"RFOO","RFOA","RFOL","RFOP"}, {1e4}); // 1e4 : Not the same ohelperin
    compare_segment_motion(trial, "L.Foot.SCS", {"LFOO","LFOA","LFOL","LFOP"}, {1e4}); // 1e4 : Not the same ohelperin
  };
  
  CXXTEST_TEST(reconstruct3BothLowerBodyFF)
  {
    ma::body::PluginGait helper(ma::body::Region::Lower, ma::body::Side::Both);
    helper.setMarkerDiameter(14.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(920.0); // mm
    helper.setLeftKneeWidth(102.0); // mm
    helper.setLeftAnkleWidth(70.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(920.0); // mm
    helper.setRightKneeWidth(102.0); // mm
    helper.setRightAnkleWidth(70.0); // mm
    
    ma::Node rootCalibration("rootCalibration"), rootDynamic("rootDynamic"), rootModel("rootModel");
    generate_trial_from_file(&rootCalibration, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration3_FF.c3d"));
    TS_ASSERT(helper.calibrate(&rootCalibration, nullptr));
    generate_trial_from_file(&rootDynamic, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Motion3_FF.c3d"));
    TS_ASSERT(helper.reconstruct(&rootModel, &rootDynamic));

    auto trial = rootDynamic.findChild<ma::Trial*>();
    compare_segment_motion(trial, "Pelvis.SCS", {"PELO","PELA","PELL","PELP"}, {5e-4});
    compare_segment_motion(trial, "R.Thigh.SCS", {"RFEO","RFEA","RFEL","RFEP"}, {5e-4});
    compare_segment_motion(trial, "L.Thigh.SCS", {"LFEO","LFEA","LFEL","LFEP"}, {5e-4});
    compare_segment_motion(trial, "R.Shank.SCS", {"RTIO","RTIA","RTIL","RTIP"}, {5e-4});
    compare_segment_motion(trial, "L.Shank.SCS", {"LTIO","LTIA","LTIL","LTIP"}, {5e-4});
    compare_segment_motion(trial, "R.Foot.SCS", {"RFOO","RFOA","RFOL","RFOP"}, {1e4}); // 1e4 : Not the same ohelperin
    compare_segment_motion(trial, "L.Foot.SCS", {"LFOO","LFOA","LFOL","LFOP"}, {1e4}); // 1e4 : Not the same ohelperin
  };
  
  CXXTEST_TEST(reconstruct3BothLowerBodyFF_N18)
  {
    ma::body::PluginGait helper(ma::body::Region::Lower, ma::body::Side::Both);
    helper.setMarkerDiameter(14.0); // mm
    helper.setLeftFootFlat(true);
    helper.setLeftLegLength(920.0); // mm
    helper.setLeftKneeWidth(102.0); // mm
    helper.setLeftAnkleWidth(70.0); // mm
    helper.setRightFootFlat(true);
    helper.setRightLegLength(920.0); // mm
    helper.setRightKneeWidth(102.0); // mm
    helper.setRightAnkleWidth(70.0); // mm
    
    ma::Node rootCalibration("rootCalibration"), rootDynamic("rootDynamic"), rootModel("rootModel");
    generate_trial_from_file(&rootCalibration, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration3_FF_N18.c3d"));
    TS_ASSERT(helper.calibrate(&rootCalibration, nullptr));
    generate_trial_from_file(&rootDynamic, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Motion3_FF_N18.c3d"));
    TS_ASSERT(helper.reconstruct(&rootModel, &rootDynamic));

    auto trial = rootDynamic.findChild<ma::Trial*>();
    compare_segment_motion(trial, "Pelvis.SCS", {"PELO","PELA","PELL","PELP"}, {5e-4});
    compare_segment_motion(trial, "R.Thigh.SCS", {"RFEO","RFEA","RFEL","RFEP"}, {5e-4});
    compare_segment_motion(trial, "L.Thigh.SCS", {"LFEO","LFEA","LFEL","LFEP"}, {5e-4});
    compare_segment_motion(trial, "R.Shank.SCS", {"RTIO","RTIA","RTIL","RTIP"}, {5e-4});
    compare_segment_motion(trial, "L.Shank.SCS", {"LTIO","LTIA","LTIL","LTIP"}, {5e-4});
    compare_segment_motion(trial, "R.Foot.SCS", {"RFOO","RFOA","RFOL","RFOP"}, {1e4}); // 1e4 : Not the same ohelperin
    compare_segment_motion(trial, "L.Foot.SCS", {"LFOO","LFOA","LFOL","LFOP"}, {1e4}); // 1e4 : Not the same ohelperin
  };
  
  CXXTEST_TEST(reconstruct3BothLowerBodyNoFF)
  {
    ma::body::PluginGait helper(ma::body::Region::Lower, ma::body::Side::Both);
    helper.setMarkerDiameter(14.0); // mm
    helper.setLeftLegLength(920.0); // mm
    helper.setLeftKneeWidth(102.0); // mm
    helper.setLeftAnkleWidth(70.0); // mm
    helper.setRightLegLength(920.0); // mm
    helper.setRightKneeWidth(102.0); // mm
    helper.setRightAnkleWidth(70.0); // mm
    
    ma::Node rootCalibration("rootCalibration"), rootDynamic("rootDynamic"), rootModel("rootModel");
    generate_trial_from_file(&rootCalibration, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Calibration3_noFF.c3d"));
    TS_ASSERT(helper.calibrate(&rootCalibration, nullptr));
    generate_trial_from_file(&rootDynamic, OPENMA_TDD_PATH_IN("c3d/plugingait/PiG_Motion3_noFF.c3d"));
    TS_ASSERT(helper.reconstruct(&rootModel, &rootDynamic));

    auto trial = rootDynamic.findChild<ma::Trial*>();
    compare_segment_motion(trial, "Pelvis.SCS", {"PELO","PELA","PELL","PELP"}, {5e-4});
    compare_segment_motion(trial, "R.Thigh.SCS", {"RFEO","RFEA","RFEL","RFEP"}, {5e-4});
    compare_segment_motion(trial, "L.Thigh.SCS", {"LFEO","LFEA","LFEL","LFEP"}, {5e-4});
    compare_segment_motion(trial, "R.Shank.SCS", {"RTIO","RTIA","RTIL","RTIP"}, {5e-4});
    compare_segment_motion(trial, "L.Shank.SCS", {"LTIO","LTIA","LTIL","LTIP"}, {5e-4});
    compare_segment_motion(trial, "R.Foot.SCS", {"RFOO","RFOA","RFOL","RFOP"}, {1e4}); // 1e4 : Not the same ohelperin
    compare_segment_motion(trial, "L.Foot.SCS", {"LFOO","LFOA","LFOL","LFOP"}, {1e4}); // 1e4 : Not the same ohelperin
  };
};

CXXTEST_SUITE_REGISTRATION(PluginGaitTest)
  
CXXTEST_TEST_REGISTRATION(PluginGaitTest, calibrateLeftFullBodyOneFrame)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, calibrateRightFullBodyOneFrame)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, calibrateBothFullBodyOneFrame)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, calibrateBothUpperBodyFullFrames)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, calibrateBothLowerBodyFullFrames)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, calibrateBothFullBodyFullFrames)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, calibrateBothFullBodyHoleFrames)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, calibrate2BothFullBodyNoOption)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, calibrate3BothLowerBodyFF)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, calibrate3BothLowerBodyFF_N18)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, calibrate3BothLowerBodynoFF)

CXXTEST_TEST_REGISTRATION(PluginGaitTest, reconstructBothLowerBodyOneFrame)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, reconstructBothUpperBodyOneFrame)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, reconstructBothLowerBodyHoleFrames)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, reconstructBothUpperBodyHoleFrames)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, reconstructBothFullBodyFullFrames)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, reconstruct3BothLowerBodyFF)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, reconstruct3BothLowerBodyFF_N18)
CXXTEST_TEST_REGISTRATION(PluginGaitTest, reconstruct3BothLowerBodyNoFF)