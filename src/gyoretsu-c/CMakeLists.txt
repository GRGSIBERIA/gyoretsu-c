# CMakeList.txt : gyoretsu-c の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.8)

project ("gyoretsu-c")

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (gyoretsu-c "gyoretsu-c.c" "gyoretsu-c.h" "libraries.c")

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
