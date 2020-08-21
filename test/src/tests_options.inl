#define ARGC(argv) (sizeof(argv) / sizeof(char*))

TEST_CASE("options::bool")
{
    const char* argv[] =
    { 
        "program.exe",
        "-b",
        "-c", "true",
        "true"
    };

    Options options("program");
    options.add({ "-a" }, "", Options::value<bool>()->optional());
    options.add({ "-b" }, "", Options::value<bool>());
    options.add({ "-c" }, "", Options::value<bool>());
    options.add({ "-d" }, "", Options::value<bool>(true));
    options.add({  "e" }, "", Options::value<bool>()->positional());
    
    OptionsResult result = options.parse(ARGC(argv), argv);
    REQUIRE(!result.has("-a"));
    REQUIRE( result.get<bool>("-b"));
    REQUIRE( result.get<bool>("-c"));
    REQUIRE( result.get<bool>("-d"));
    REQUIRE( result.get<bool>( "e"));
}

TEST_CASE("options::int")
{
    const char* argv[] =
    { 
        "program.exe",
        "-b", "1",
        "-c", "2",
        "8"
    };

    Options options("program");
    options.add({ "-a" }, "", Options::value<int>()->optional());
    options.add({ "-b" }, "", Options::value<int>());
    options.add({ "-c" }, "", Options::value<int>());
    options.add({ "-d" }, "", Options::value<int>(4));
    options.add({  "e" }, "", Options::value<int>()->positional());
    
    OptionsResult result = options.parse(ARGC(argv), argv);
    REQUIRE(!result.has("-a"));
    REQUIRE( result.get<int>("-b") == 1);
    REQUIRE( result.get<int>("-c") == 2);
    REQUIRE( result.get<int>("-d") == 4);
    REQUIRE( result.get<int>( "e") == 8);
}

TEST_CASE("options::double")
{
    const char* argv[] =
    { 
        "program.exe",
        "-b", "1.1",
        "-c", "2.1",
        "8.1"
    };

    Options options("program");
    options.add({ "-a" }, "", Options::value<double>()->optional());
    options.add({ "-b" }, "", Options::value<double>());
    options.add({ "-c" }, "", Options::value<double>());
    options.add({ "-d" }, "", Options::value<double>(4.1));
    options.add({  "e" }, "", Options::value<double>()->positional());
    
    OptionsResult result = options.parse(ARGC(argv), argv);
    REQUIRE(!result.has("-a"));
    REQUIRE( result.get<double>("-b") == 1.1);
    REQUIRE( result.get<double>("-c") == 2.1);
    REQUIRE( result.get<double>("-d") == 4.1);
    REQUIRE( result.get<double>( "e") == 8.1);
}

TEST_CASE("options::string")
{
    const char* argv[] =
    { 
        "program.exe",
        "-b", "test1",
        "-c", "test2",
        "test4"
    };

    Options options("program");
    options.add({ "-a" }, "", Options::value<std::string>()->optional());
    options.add({ "-b" }, "", Options::value<std::string>());
    options.add({ "-c" }, "", Options::value<std::string>());
    options.add({ "-d" }, "", Options::value<std::string>("test3"));
    options.add({  "e" }, "", Options::value<std::string>()->positional());
    
    OptionsResult result = options.parse(ARGC(argv), argv);
    REQUIRE(!result.has("-a"));
    REQUIRE( result.get<std::string>("-b") == "test1");
    REQUIRE( result.get<std::string>("-c") == "test2");
    REQUIRE( result.get<std::string>("-d") == "test3");
    REQUIRE( result.get<std::string>( "e") == "test4");
}

TEST_CASE("options::OptionError1")
{
    const char* argv1[] = { "program.exe", "-x" };
    const char* argv2[] = { "program.exe", "-x", "wrong" };
    const char* argv3[] = { "program.exe", "-x", "wrong" };

    Options options1("program");
    Options options2("program");
    Options options3("program");

    options1.add({ "-x" }, "", Options::value<int>());
    options2.add({ "-x" }, "", Options::value<int>());
    options3.add({ "-x" }, "", Options::value<bool>());

    CHECK_THROWS_AS(options1.parse(ARGC(argv1), argv1), OptionError);
    CHECK_THROWS_AS(options2.parse(ARGC(argv2), argv2), OptionError);
    CHECK_THROWS_AS(options3.parse(ARGC(argv3), argv3), OptionError);
}

TEST_CASE("options::OptionError2")
{
    const char* argv1[] = { "program.exe" };
    const char* argv2[] = { "program.exe" };

    Options options1("program");
    Options options2("program");

    options1.add({ "-x" }, "", Options::value<int>());
    options2.add({  "x" }, "", Options::value<int>()->positional());

    CHECK_THROWS_AS(options1.parse(ARGC(argv1), argv1), OptionError);
    CHECK_THROWS_AS(options2.parse(ARGC(argv2), argv2), OptionError);
}

TEST_CASE("options::OptionError3")
{
    Options options("program");
    options.add({ "-x" }, "", Options::value<bool>());
    options.add({  "x" }, "", Options::value<bool>()->positional());

    CHECK_THROWS_AS(options.add({ "-x" }, "", Options::value<bool>()), OptionError);
    CHECK_THROWS_AS(options.add({  "x" }, "", Options::value<bool>()), OptionError);
}

TEST_CASE("options::OptionError4")
{
    const char* argv[] = { "program.exe" };

    Options options("program");
    OptionsResult result = options.parse(ARGC(argv), argv);

    CHECK_THROWS_AS(result.get<int>("-x"), OptionError);
    CHECK_THROWS_AS(result.get<int>("-y"), OptionError);
    CHECK_THROWS_AS(result.get<int>("-z"), OptionError);
}

TEST_CASE("options::help")
{
    Options options("program");
    options.add({ "--aa", "-a" }, "This is a", Options::value<bool>());
    options.add({ "--bb", "-b" }, "This is b", Options::value<int>()->optional());
    options.add({ "--cc", "-c" }, "This is c", Options::value<double>(1.1));
    options.add({   "dd",  "d" }, "This is d", Options::value<std::string>()->positional());
    options.add({   "ee",  "e" }, "This is e", Options::value<bool>()->positional()->optional());
    options.add({   "ff",  "f" }, "This is f", Options::value<std::string>("test")->positional());

    fmt::print(options.help());
}

#undef ARGC