﻿# О проекте

В этом проекте находится принтер файла формата Measurelook для языка Си.
Принтер реализован на основе bstring. В репозитории приведен полный пример
организации вычислительного эксперимента, для демонстрации работы принтера
на живом примере.

Проект сделан по шаблону из книги Зеда Шоу (Zed Shaw) Learn C The Hard Way.

# Установка и запуск

0. Скачать репозиторий
1. make

Проверялось на gcc 4.4.6.

# Структура проекта

- src
  - lcthw
    - mlBuilder - (от measurelook builder) - принтер файла Measurelook
    - bstrlib - [библиотека работы со строками в Си](http://bstring.sourceforge.net/)
  - distances - функции вычисления расстояний
  - distancesPerformanceTest - тест производительности для функций вычисления расстояний
  - env - вспомогательные функции получения параметров окружения в рантайме
  - mlExtras - переиспользуемый вывод параметров окружения в результаты эксперимента
  - dbg.h - отладочные макросы Зеда Шоу
- testRes/distances - результаты запуска тестов производительности
- tests
  - env_tests - тесты получения переменных окружения в рантайме
  - distances_performance_tests - запуск тестов производительности
  - minunit.h - автозапуск тестов 
  - runtests.sh - автозапуск тестов 