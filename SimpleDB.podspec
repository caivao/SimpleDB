
Pod::Spec.new do |s|
  s.name             = 'SimpleDB'
  s.version          = '0.1.0'
  s.summary          = 'SQLite ORM database'

  s.description      = <<-DESC
                        SQLite ORM database module
                       DESC

  s.homepage         = 'https://github.com/caivao/SimpleDB'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'lifeng.zheng' => '287956632@qq.com' }
  s.source           = { :git => 'git@github.com:caivao/SimpleDB.git', :tag => s.version.to_s }

  s.ios.deployment_target = '9.0'
  s.public_header_files = "SimpleDB/src/SDB.h", "SimpleDB/src/**/*.{h,hpp}"
  s.source_files  = "SimpleDB/src/SDB.h", "SimpleDB/src/**/*.{h,m,hpp,cpp,mm}"
  s.frameworks = "CoreFoundation", "Foundation"
  s.ios.frameworks = "UIKit"
  s.libraries = "z", "c++"
  s.requires_arc = true
  s.pod_target_xcconfig = {
    "LIBRARY_SEARCH_PATHS[sdk=macosx*]" => "$(SDKROOT)/usr/lib/system",
    "CLANG_CXX_LANGUAGE_STANDARD" => "gnu++0x",
    "CLANG_CXX_LIBRARY" => "libc++",
    "OTHER_CFLAGS" => "-fvisibility-inlines-hidden",
    "OTHER_CPLUSPLUSFLAGS" => "-fvisibility-inlines-hidden",
  }

end
