# Gooey - CAN-D Explorer

A cross-platform Graphical User Interface (GUI) for the CAN-D vehicle data logger.

## Getting Started

These instructions lists the steps required to run the CAN-D GUI.

### Prerequisites

What things you need to install the software and how to install them

1. Python3 (3.7 if possible). Install either through https://www.python.org/ or brew

```
brew install python
```

2. Install the dependencies

```
pip install -r requirements
```

3. Install this package

```
pip install -e .
```

### Running

Go to the ./gooey/ directory

```
cd ./gooey/
```

Run gui.py using python 3

```
python3 gui.py
```

## Built With

- [PyQt5](https://pypi.org/project/PyQt5/) - Cross-platform UI toolkit
- [pip](https://pypi.org/project/pip/) - Dependency Management
- [cantools](https://pypi.org/project/cantools/) - CAN python package for decoding/encoding
