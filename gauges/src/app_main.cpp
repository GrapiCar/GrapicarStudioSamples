#include <grapi/assist/application.h>
#include <grapi/runtime/project_manager.h>
#include <grapi/runtime/utils.h>

#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <locale>

using grapi::base::String;
using grapi::assist::Config;
using grapi::assist::Application;
using grapi::runtime::ProjectManager;

#ifdef WIN32
void setAppLocale() {
  // --- 로케일 설정 (프로그램 시작 시 한 번) ---
  // 환경 변수로부터 로케일 설정 시도 (Linux에서 UTF-8 환경에 자주 사용됨)
  if (setlocale(LC_ALL, "ko_KR.UTF-8") == nullptr) {
    std::cerr << "Warning: Could not set locale from environment. "
                 "Using default 'C' locale."
              << std::endl;

    // UTF-8이 아닌 경우 한글 등 멀티바이트 문자 변환이 실패할 수 있음
    // 특정 UTF-8 로케일을 명시적으로 시도해볼 수 있음:
    // setlocale(LC_ALL, "en_US.UTF-8"); 또는 setlocale(LC_ALL, ".UTF8");
  }

  // C++ 스트림 로케일 설정 (wcout 사용 시 필요)
  try {
    // 전역 C++ 로케일 설정
    std::locale::global(std::locale("ko_KR.UTF-8"));
    // wcout에 로케일 적용
    std::wcout.imbue(std::locale("ko_KR.UTF-8"));
    // cout에도 적용 (선택 사항)
    std::cout.imbue(std::locale("ko_KR.UTF-8"));
  } catch (const std::runtime_error& e) {
    std::cerr << "Warning: Failed to set C++ locale: " << e.what() << std::endl;
  }
}
#endif 

String getBuildJSONPath(std::filesystem::path& exe_dir) {
  std::filesystem::path project_filepath; // 최종 프로젝트 파일 경로

  // 1. 실행 파일 디렉토리 기준으로 'build' 디렉토리 경로 계산
  //  가정: 'build' 디렉토리가 실행 파일 디렉토리의 *부모* 디렉토리에 있음
  //  (예: 실행파일이 .../bin/myapp 이고, 빌드파일은 .../build/build.json)
  //  실제 구조에 맞게 "../build" 부분을 수정해야 합니다.
  std::filesystem::path build_dir_relative = exe_dir / "../prjout";

  // 2. build.json 파일의 전체 경로 생성
  project_filepath = build_dir_relative / "build.json";
  std::cout << "Calculated project file path: " << project_filepath
            << std::endl;

  // 3. 경로 정규화 및 실제 존재 확인 (canonical 사용)
  //  '..' 등을 해석하고, 심볼릭 링크를 따라가며, 절대 경로로 만듭니다.
  //  경로가 존재하지 않으면 filesystem_error 예외 발생
  project_filepath = std::filesystem::canonical(project_filepath);
  std::cout << "Canonicalized project file path: " << project_filepath
            << std::endl;

  return project_filepath.string();
}

String getProjectSettingPath(std::filesystem::path& exe_dir) {
  // 프로젝트 설정 파일(*.xpj) 경로 찾기
  std::filesystem::path project_settings_filepath;
  std::filesystem::path parent_dir = exe_dir.parent_path();
  bool project_settings_found = false;

  for (const auto& entry : std::filesystem::directory_iterator(parent_dir)) {
    if (entry.is_regular_file() && entry.path().extension() == ".xpj") {
      project_settings_filepath = std::filesystem::canonical(entry.path());
      project_settings_found = true;

      std::cout << "Found project settings file: " << project_settings_filepath
                << std::endl;
      break; // 첫 번째로 찾은 파일 사용
    }
  }

  if (!project_settings_found) {
    throw std::runtime_error("Project settings file (*.xpj) not found in "
                             + parent_dir.string());
  }

  return project_settings_filepath.string();
}

#ifdef WIN32
int wmain(int argc, wchar_t* argv[]) {
#else
int main(int argc, char** argv) {
#endif
  Config config;
  Application& app = Application::get();
  ProjectManager* pm = nullptr;

#ifdef WIN32
  // grapi::base::WString 사용을 위한 설정
  setAppLocale();
#endif

  if ((argc <= 0) || (argv[0] == nullptr)) {
    std::cerr << "Could not get the executable path from argv[0]." << std::endl;
    return 1;
  }

  // 실행 파일이 있는 디렉토리 경로 얻기
  // std::filesystem::absolute는 argv[0]가 완전한 경로가 아닐 경우
  // CWD를 기준으로 할 수 있음
  std::filesystem::path exe_uri = std::filesystem::absolute(argv[0]);
  std::filesystem::path exe_dir = exe_uri.parent_path();

  std::cout << "Executable file directory: " << exe_dir << std::endl;

  String root_uri = exe_dir.parent_path().string();
  String setting_uri = getProjectSettingPath(exe_dir);
  String project_uri = getBuildJSONPath(exe_dir);

  pm = new ProjectManager();
  grapi::runtime::initUtils(pm->getLoader()); // 전역 유틸리티 초기화
  pm->loadSettings(setting_uri);

  config.title = pm->getName();
  config.resizable = false;
  #ifdef __QNX__
  config.backend = grapi::base::Backend::kOpenGL;
  #else
  //config.backend = grapi::base::Backend::kVulkan;
  config.backend = pm->getBackend();
  #endif

  auto setup = [&pm, root_uri, project_uri]() {
    Application& app = Application::get();

    pm->initEngine();
    
    pm->resize(app.getWidth(), app.getHeight(), app.getNativeWindow());
    pm->setRootURI(root_uri);

    std::cout << "Attempting to load project: " << project_uri << std::endl;

    pm->load(project_uri);
#ifdef _DEBUG
    pm->printDebugInfo();
#endif
    pm->start();
  };

  auto animate = [&pm](vfloat delta)-> bool {
    pm->update(delta);
    return true;
  };

  auto resize = [&pm]() {
    Application& app = Application::get();
    pm->resize(app.getWidth(), app.getHeight(), app.getNativeWindow());
  };

  auto cleanup = [&pm]() {
    pm->destroyEngine();
  };

  app.setConfiguration(config);
  app.setup(setup);
  app.cleanup(cleanup);
  app.animate(animate);
  app.resize(resize);
  app.initialize(pm->getRootURI(), 0, 0, 0, pm->getWidth(), pm->getHeight(),
                 nullptr);
  app.run();

  delete pm;

  return 0;
}
