CXX_9=g++9.1
CXX=g++
CXXVERSION= -std=c++11
CXXFLAGS= -g -fprofile-arcs -ftest-coverage

LIBS_LOCAL = libs
LINKFLAGS_REST = -lrestbed -lpthread
LINKFLAGS_TEST = -lgtest -lgmock -lpthread
LINKFLAGS_WINSOCK = -lws2_32 -lwsock32
LINKFLAGS_VICTOR = -lpthread
SRC_DIR_SERVER = src/server
SRC_DIR_CLIENT = src/client
SRC_DIR_SERVICE = src/service
SRC_DIR_VICTORTEST = src/victor-test

TEST_DIR = test
INCLUDE_RESTBED = -I include/restbed
INCLUDE_JSON = -I include/json
INCLUDE_SERVICE = -I include/service

SRC_INCLUDE = include
SERVICE_INCLUDE = include/service

GCOV_9 = gcov9.1
GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

MEMCHECK_RESULTS = ValgrindOut.xml

STATIC_ANALYSIS = cppcheck

STATIC_RESULTS = CppCheckResults.xml

BROWSER = firefox

STYLE_CHECK = cpplint.py
STYLE_CHECK_LOCAL = cpplint

PROGRAM_SERVER = issueServer
PROGRAM_CLIENT = issueClient
PROGRAM_TEST = issueTest
PROGRAM_VICTORTEST = victorTest

.PHONY: all
all: $(PROGRAM_SERVER) $(PROGRAM_CLIENT) $(PROGRAM_TEST) memcheck-test coverage docs static style

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o $(TEST_SRC)/*.o *.gcov *.gcda *.gcno \
	$(COVERAGE_RESULTS) \
	$(PROGRAM_SERVER) \
	$(PROGRAM_TEST) \
	$(PROGRAM_CLIENT) \
	$(PROGRAM_VICTORTEST) \
	$(MEMCHECK_RESULTS) \
	$(COVERAGE_DIR) \
	$(STATIC_RESULTS) \
	dat \
	docs

.PHONY: server
server: $(PROGRAM_SERVER)

.PHONY: server_win
server_win: $(PROGRAM_SERVER)_win

.PHONY: client
client: $(PROGRAM_CLIENT)

.PHONY: client_win
client_win: $(PROGRAM_CLIENT)_win

.PHONY: victortest
victortest: $(PROGRAM_VICTORTEST)

.PHONY: runserver
runserver: server
	./${PROGRAM_SERVER} &

.PHONY: runserver_win
runserver_win: server_win
	./${PROGRAM_SERVER}.exe

.PHONY: stopserver
stopserver:
	kill -9 ${PROGRAM_SERVER}

.PHONY: stopserver_win
stopserver_win:
	taskkill /F /IM ${PROGRAM_SERVER}.exe

$(PROGRAM_SERVER): $(SRC_DIR_SERVER) $(SRC_DIR_SERVICE)
	$(CXX_9) $(CXXFLAGS) -o $(PROGRAM_SERVER) $(INCLUDE_SERVICE) \
	$(SRC_DIR_SERVER)/*.cpp $(SRC_DIR_SERVICE)/*.cpp $(LINKFLAGS_REST)

$(PROGRAM_SERVER)_ryan: $(SRC_DIR_SERVER) $(SRC_DIR_SERVICE)
	$(CXX) -std=c++14 $(CXXFLAGS) \
	-o $(PROGRAM_SERVER) $(INCLUDE_SERVICE) $(INCLUDE_JSON) \
	$(SRC_DIR_SERVER)/*.cpp $(SRC_DIR_SERVICE)/*.cpp $(LINKFLAGS_REST)

$(PROGRAM_SERVER)_win: $(SRC_DIR_SERVER) $(SRC_DIR_SERVICE)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_SERVER) $(INCLUDE_SERVICE) \
	$(INCLUDE_RESTBED) $(INCLUDE_JSON) \
	$(SRC_DIR_SERVER)/*.cpp $(SRC_DIR_SERVICE)/*.cpp -L$(LIBS_LOCAL) \
	$(LINKFLAGS_REST) $(LINKFLAGS_WINSOCK)

$(PROGRAM_CLIENT): $(SRC_DIR_CLIENT)
	$(CXX_9) $(CXXFLAGS) -o $(PROGRAM_CLIENT) \
	$(SRC_DIR_CLIENT)/*.cpp $(LINKFLAGS_REST)

$(PROGRAM_CLIENT)_ryan: $(SRC_DIR_CLIENT)
	$(CXX) -std=c++14 $(CXXFLAGS) -o $(PROGRAM_CLIENT) $(INCLUDE_JSON) \
	$(SRC_DIR_CLIENT)/*.cpp $(LINKFLAGS_REST)

$(PROGRAM_CLIENT)_win: $(SRC_DIR_CLIENT)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_CLIENT) \
	$(INCLUDE_RESTBED) $(INCLUDE_JSON) \
	$(SRC_DIR_CLIENT)/*.cpp -L$(LIBS_LOCAL) \
	$(LINKFLAGS_REST) $(LINKFLAGS_WINSOCK)

$(PROGRAM_TEST): $(TEST_DIR) $(SRC_DIR_SERVICE)
	$(CXX) -std=c++11 $(CXXFLAGS) -o $(PROGRAM_TEST) $(INCLUDE_SERVICE) $(INCLUDE_JSON) \
	$(TEST_DIR)/*.cpp $(SRC_DIR_SERVICE)/*.cpp $(LINKFLAGS_TEST)

$(PROGRAM_VICTORTEST): $(SRC_DIR_VICTORTEST)
	$(CXX) -std=c++11 $(CXXFLAGS) -o $(PROGRAM_VICTORTEST) \
	$(INCLUDE_SERVICE) \
	$(SRC_DIR_VICTORTEST)/*.cpp $(SRC_DIR_SERVICE)/*.cpp \
	$(LINKFLAGS_VICTOR)

.PHONY: tests
tests: $(PROGRAM_TEST)
	./$(PROGRAM_TEST)

.PHONY: memcheck
memcheck: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM_TEST)

.PHONY: fullmemcheck
fullmemcheck: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=full $(PROGRAM_TEST)

.PHONY: memcheck-test
memcheck-test: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM_TEST)

.PHONY: coverage
coverage: $(PROGRAM_TEST)
	./$(PROGRAM_TEST)
	# Determine code coverage
	$(LCOV) --capture --gcov-tool $(GCOV) --directory . --output-file $(COVERAGE_RESULTS) --rc lcov_branch_coverage=1
	$(LCOV) --extract $(COVERAGE_RESULTS) */$(SRC_DIR_SERVICE)/* -o $(COVERAGE_RESULTS) --rc lcov_branch_coverage=1
	genhtml $(COVERAGE_RESULTS)  --output-directory $(COVERAGE_DIR) --rc lcov_branch_coverage=1
	#Remove all of the generated files from gcov
	rm -f *.gc*

.PHONY: static
static: ${SRC_DIR_SERVER} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVICE} ${TEST_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR_SERVER} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVICE} ${TEST_DIR} ${SERVICE_INCLUDE} --suppress=missingInclude

.PHONY: style
style: ${SRC_DIR_SERVICE} ${TEST_DIR} ${SERVICE_INCLUDE} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVER}
	${STYLE_CHECK} ${SERVICE_INCLUDE}/* ${SRC_DIR_SERVICE}/* ${SRC_DIR_CLIENT}/* ${SRC_DIR_SERVER}/*

.PHONY: style-local
style-local: ${SRC_DIR_SERVICE} ${TEST_DIR} ${SERVICE_INCLUDE} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVER}
	${STYLE_CHECK_LOCAL} ${SERVICE_INCLUDE}/* ${SRC_DIR_SERVICE}/* ${SRC_DIR_CLIENT}/* ${SRC_DIR_SERVER}/*


.PHONY: docs
docs: ${SERVICE_INCLUDE} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVER}
	doxygen doxyfile
