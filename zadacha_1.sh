#!/bin/bash 
 
# Функция отображения справочного сообщения
function display_help() { 
  echo "Usage: $0 [OPTION]... 
 
  -u, --users 
    Display list of users and their home directories, sorted alphabetically. 
 
  -p, --processes 
    Display list of running processes, sorted by their identifiers. 
 
  -h, --help 
    Display this help message and exit. 
 
  -l PATH, --log PATH 
    Redirect output to file at specified path. 
 
  -e PATH, --errors PATH 
    Redirect error output to file at specified path. 
 
  -v, --version 
    Display version information and exit. 
 
  -d, --debug 
    Enable debug mode." 
} 
 
# Функция отображения информации о версии
function display_version() { 
  echo "Console Utility v1.0" 
} 
 
# Функция отображения пользователей и их домашних каталогов 
function display_users() { 
  getent passwd | awk -F: '{print $1 " " $6}' | sort 
} 
 
# Функция для отображения запущенных процессов
function display_processes() { 
  ps aux | sort -k2 -n 
} 
 
# Функция для перенаправления выходных данных в указанный файл
function redirect_output() { 
  local path=$1 
  if [[ ! -d "${path%/*}" ]]; then 
    echo "Error: Invalid directory path." 
    return 1 
  fi 
 
  if [[ ! -w "${path}" ]]; then 
    echo "Error: Cannot write to file." 
    return 1 
  fi 
 
  if [[ "$#" -eq 1 ]]; then 
    exec >"$path" 
  else 
    exec 2>"$path" 
  fi 
} 
 
# Функция для включения режима отладки
function enable_debug() { 
  set -x 
} 
 
# Анализ параметров командной строки
while [[ $# -gt 0 ]]; do 
  key="$1" 
 
  case $key in 
    -u|--users) 
      display_users 
      shift 
      ;; 
    -p|--processes) 
      display_processes 
      shift 
      ;; 
    -h|--help) 
      display_help 
      exit 0 
      ;; 
    -l|--log) 
      redirect_output "$2" 
      shift 
      shift 
      ;; 
    -e|--errors) 
      redirect_output "$2" 2>&1 
      shift 
      shift 
      ;; 
    -v|--version) 
      display_version 
      exit 0 
      ;; 
    -d|--debug) 
      enable_debug 
      shift 
      ;; 
    *) 
      echo "Error: Invalid option." 
      display_help 
      exit 1 
      ;; 
  esac 
done 
 
# Если параметры не заданы, отобразите пользователей
if [[ $# -eq 0 ]]; then 
  display_users 
fi
