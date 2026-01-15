import subprocess, shutil

subprocess.check_call(['cmake', '--preset=vcpkg'])
subprocess.check_call(['cmake', '--build', 'build', '--config', 'Release'])
shutil.copyfile('./build/cpp/Release/dcc_core.cp312-win_amd64.pyd', './src/dcc/dcc_core.pyd')