# **SimpleDebog**

A custom debugger for Linux and macOS using **Qt6** for the GUI.

---

## **📌 Dependencies**

Before compiling, install the required libraries:

### **🟢 Debian/Ubuntu**
```sh
sudo apt update && sudo apt install -y \
    cmake g++ \
    qt6-base-dev \
    libcapstone-dev \
    libunwind-dev \
    binutils-dev
```

### **🔵 Fedora**
```sh
sudo dnf install -y \
    cmake gcc-c++ \
    qt6-qtbase-devel \
    capstone-devel \
    libunwind-devel \
    binutils-devel
```

### **🍎 macOS (Homebrew)**
```sh
brew install cmake qt@6 capstone libunwind binutils
```

> ℹ️ On macOS with Homebrew, make sure to add Qt to your `CMAKE_PREFIX_PATH` if needed:
> ```sh
> export CMAKE_PREFIX_PATH=$(brew --prefix qt@6)
> ```

---

## **🔧 Build Instructions**

Run the following script to **build, rebuild, or clean the project**:

```sh
./compile build   # Build everything from scratch
./compile re      # Rebuild only the code, keeping external libraries
./compile clean   # Remove the build directory
```

Alternatively, build manually:

```sh
mkdir -p build
cd build
cmake ..
make
```

---

## **🎯 Running the Debugger**

After compiling, run the debugger with:
```sh
./SimpleDebog
```

---

## 📄 License

This project is licensed under the [Apache License 2.0](./LICENSE).

## 🤝 Contributing

We welcome contributions from the community!

By submitting code, you agree to the terms of our [Contributor License Agreement (CLA)](./CLA.md).  
This ensures that **SliFerBlaze and ArthurSpiller** retain the right to relicense and maintain the project.

Don't forget to add your name to [CONTRIBUTORS.md](./CONTRIBUTORS.md) if you'd like public credit!

## **💡 Notes:**

- This project **does not support Windows**.
- Qt6 provides a modern and flexible GUI.
- It can **debug multiple binary formats**, not just ELF.
- If you run into missing libraries, check your package manager (`apt`, `dnf`, `brew`).

