# Advanced Systems Programming - Worksheet 1

## Contents
<ul>
    <li><a href="#description">Description</a></li>
    <li><a href="#dependencies">Dependencies</a></li>
    <li><a href="#compiling">Compiling and Running the Files</a></li>
    <li><a href="#tasks">Tasks</a></li>
</ul>

<h2 id="description">Description</h2>

The first aim of this project is to create a smaller scale, but functioning, user-created C-Style string class.<br>

The second aim is to create and demonstrate how reference counting in regards to memory manipulation works.

<h2 id="dependencies">Dependencies</h2>

<ul>
<li><a href="https://releases.llvm.org/download.html">Clang</a>: For compiling the source files (USING C++17).
<li><a href="https://ftp.gnu.org/gnu/make/">GNU Make</a>: For building and running the project.</li>
</ul>

<h2 id="compiling">Compiling and Running the Files</h2>
<p style="font-style: italic; font-size: 12px;">NOTE: ENSURE DEPENDENCIES ARE INSTALLED IF NOT USING CSCTCLOUD</p>
<li>First to build the src files, run in the terminal (in root directory):<br><br>

```bash
make
```

<br>
<li>Then to run a task, run in the terminal (in root directory):</li><br>

```bash
make run <Folder Name>
```
Example:

    make run Task2

<h2 id="tasks">Tasks</h2>
<li><a href="#task1">Task 1</a></li>
<li><a href="#task2">Task 2</a></li>
<li><a href="#task3">Task 3</a></li>
<li><a href="#task4">Task 4</a></li>

<h3 id="task1">Task 1</h3>
Task 1 aims to create a simple replica of the C-style string class. 