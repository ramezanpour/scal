# SCAL -- a simple CLI-based Persian calendar

## Introduction

Scal is a very simple CLI-based Persian calendar that displays the current **Shamsi** month calendar and highlights the current date. The following is a screennshot:

![Scal Screenshot](https://user-images.githubusercontent.com/1416456/73172575-8f743680-4118-11ea-9159-33a65bfc2f71.png)

In addition to calendar view, Scal also supports a **simple** mode that just prints the current Persian date; so, it can be used with other CLI apps such as `grep`:

```
$ scal --simple
```
Output:
```
1398-11-07
```
When using the `--simple` flag, it's also possible to customize the output format using `--format` option:
```
$ scal --simple --format "%d/%02d/%02d"
```
Output:
```
1398/11/07
```

## Get Started
Since SCAL is written in pure C, so it can be compiled for almost any target. Please use the following to get started:
```
$ git clone git@github.com:ramezanpour/scal.git
$ make
$ make install
```
