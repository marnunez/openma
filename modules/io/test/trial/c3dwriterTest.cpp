#include <cxxtest/TestDrive.h>

#include <openma/io/handlerwriter.h>
#include <openma/io/file.h>

#include "c3dhandlerTest_def.h"
#include "test_file_path.h"

CXXTEST_SUITE(C3DWriterTest)
{
  CXXTEST_TEST(capability)
  {
    ma::io::HandlerWriter writer(nullptr,"org.c3d");
    TS_ASSERT_EQUALS(writer.canWrite(), false);
    ma::io::File file;
    file.open(OPENMA_TDD_PATH_OUT("c3d/sample01_Eb015pi.c3d"), ma::io::Mode::Out);
    writer.setDevice(&file);
    TS_ASSERT_EQUALS(writer.canWrite(), true);
    TS_ASSERT_EQUALS(writer.format(), "org.c3d");
    TS_ASSERT_EQUALS(writer.errorCode(), ma::io::Error::None);
  };
  
  CXXTEST_TEST(supportedTrialFormats)
  {
    ma::io::HandlerWriter writer;
    auto formats = writer.availableFormats();
    TS_ASSERT_EQUALS(std::find(formats.cbegin(), formats.cend(), "org.c3d") != formats.cend(), true);
  };
  
  CXXTEST_TEST(detectNoDevice)
  {
    ma::io::HandlerWriter writer;
    TS_ASSERT_EQUALS(writer.canWrite(), false);
    TS_ASSERT_EQUALS(writer.errorCode(), ma::io::Error::Device);
  };
  
  CXXTEST_TEST(detectDeviceNotOpen)
  {
    ma::io::File file;
    ma::io::HandlerWriter writer(&file);
    TS_ASSERT_EQUALS(writer.canWrite(), false);
    TS_ASSERT_EQUALS(writer.errorCode(), ma::io::Error::Device);
  };

  CXXTEST_TEST(detectFail)
  {
    ma::io::File file;
    file.open(OPENMA_TDD_PATH_OUT("fail.xyz"), ma::io::Mode::Out);
    ma::io::HandlerWriter writer(&file);
    TS_ASSERT_EQUALS(writer.canWrite(), false);
    TS_ASSERT_EQUALS(writer.errorCode(), ma::io::Error::UnsupportedFormat);
  };

  CXXTEST_TEST(detectOk)
  {
    ma::io::File file;
    file.open(OPENMA_TDD_PATH_OUT("c3d/sample01_Eb015pi.c3d"), ma::io::Mode::Out);
    ma::io::HandlerWriter writer(&file);
    TS_ASSERT_EQUALS(writer.canWrite(), true);
    TS_ASSERT_EQUALS(writer.errorCode(), ma::io::Error::None);
  };
  
  CXXTEST_TEST(queryOkOne)
  {
    ma::io::File file;
    file.open(OPENMA_TDD_PATH_OUT("c3d/sample01_Eb015pi.c3d"), ma::io::Mode::Out);
    ma::io::HandlerWriter writer(&file, "org.c3d");
    TS_ASSERT_EQUALS(writer.canWrite(), true);
    TS_ASSERT_EQUALS(writer.errorCode(), ma::io::Error::None);
  };
  
  CXXTEST_TEST(queryOkTwo)
  {
    ma::io::File file;
    file.open(OPENMA_TDD_PATH_OUT("c3d/sample01_Eb015pi.c3d"), ma::io::Mode::Out);
    ma::io::HandlerWriter writer(nullptr, "org.c3d");
    writer.setDevice(&file);
    TS_ASSERT_EQUALS(writer.canWrite(), true);
    TS_ASSERT_EQUALS(writer.errorCode(), ma::io::Error::None);
  };
  
  CXXTEST_TEST(queryOkThree)
  {
    ma::io::File file;
    file.open(OPENMA_TDD_PATH_OUT("c3d/sample01_Eb015pi.c3d"), ma::io::Mode::Out);
    ma::io::HandlerWriter writer;
    writer.setDevice(&file);
    writer.setFormat("org.c3d");
    TS_ASSERT_EQUALS(writer.canWrite(), true);
    TS_ASSERT_EQUALS(writer.errorCode(), ma::io::Error::None);
  };
  
  CXXTEST_TEST(sample01Rewrited)
  {
    c3dhandlertest_rewrite_sample01("PI", "sample01_Eb015pi.c3d", OPENMA_TDD_PATH_OUT("c3d/sample01_Eb015pi.c3d"), OPENMA_TDD_PATH_IN("c3d/standard/sample01/Eb015pi.c3d"));
  }
  
  CXXTEST_TEST(sample09Rewrited)
  {
    ma::Node rootIn("rootIn"), rootOut("rootOut");
    if (!c3dhandlertest_read("", OPENMA_TDD_PATH_IN("c3d/standard/sample09/PlugInC3D.c3d"), &rootIn)) return;
    ma::TimeSequence* ts = rootIn.findChild<ma::TimeSequence*>("LHipForce");
    TS_ASSERT_EQUALS(ts->type(), ma::TimeSequence::Force);
    TS_ASSERT_EQUALS(ts->unit(), "N");
    if (!c3dhandlertest_write("", OPENMA_TDD_PATH_OUT("c3d/sample09_PlugInC3D.c3d"), &rootIn)) return;
    if (!c3dhandlertest_read("", OPENMA_TDD_PATH_OUT("c3d/sample09_PlugInC3D.c3d"), &rootOut)) return;
    ma::TimeSequence* ts2 = rootOut.findChild<ma::TimeSequence*>("LHipForce");
    TS_ASSERT_EQUALS(ts2->type(), ma::TimeSequence::Force);
    TS_ASSERT_EQUALS(ts2->unit(), "N");
    // Compare time sequences together
    TS_ASSERT_EQUALS(ts2->elements(), ts->elements());
    TS_ASSERT_EQUALS(ts2->elements(), 281 * 4);
    for (unsigned i = 0 ; i < ts->elements() ; ++i)
    {
      TS_ASSERT_DELTA(ts2->data()[i], ts->data()[i], 1e-5);
    }
  }
};

CXXTEST_SUITE_REGISTRATION(C3DWriterTest)
CXXTEST_TEST_REGISTRATION(C3DWriterTest, capability)
CXXTEST_TEST_REGISTRATION(C3DWriterTest, supportedTrialFormats)
CXXTEST_TEST_REGISTRATION(C3DWriterTest, detectNoDevice)
CXXTEST_TEST_REGISTRATION(C3DWriterTest, detectDeviceNotOpen)
CXXTEST_TEST_REGISTRATION(C3DWriterTest, detectFail)
CXXTEST_TEST_REGISTRATION(C3DWriterTest, detectOk)
CXXTEST_TEST_REGISTRATION(C3DWriterTest, queryOkOne)
CXXTEST_TEST_REGISTRATION(C3DWriterTest, queryOkTwo)
CXXTEST_TEST_REGISTRATION(C3DWriterTest, queryOkThree)
CXXTEST_TEST_REGISTRATION(C3DWriterTest, sample01Rewrited)
CXXTEST_TEST_REGISTRATION(C3DWriterTest, sample09Rewrited)