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

### **🍎 macOS (not supported yet)**

> ⚠️ macOS builds are **not currently supported** in CI.  
> You're welcome to try building manually, but compatibility is **experimental and untested**.

```sh
brew install cmake qt@6 capstone binutils
```

> ℹ️ If you try building on macOS, you may need to add Qt to your `CMAKE_PREFIX_PATH`:
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

## ✅ Commit Convention

We use [Commitizen](https://github.com/commitizen/cz-cli) for consistent commit messages.

> **Commit using:**  
> `git cz`

> ⚠️ Even though this is a C++ project, Commitizen (a Node.js tool) helps us automate changelogs and keep commits clean.

To install it:

```sh
npm install -g commitizen
```

---

## 🧼 Code Style & Formatting

### 🔧 Tools Used

- **`clang-format`** — for automatic formatting
- **`clang-tidy`** — for static analysis and code quality

✅ A `.clang-format` and optional `.clang-tidy` config are included  
✅ Formatting and linting are run automatically in CI  
✅ You can format locally with:

```sh
clang-format -i $(find . -regex '.*\.\(cpp\|c\|h\|hpp\|hh\)')
```

---

### 💻 Editor Integration

#### **🧠 VSCode**

1. Install the **Clang-Format** extension by _xaver_
2. Add this to your `settings.json`:

```json
"[cpp]": {
    "editor.defaultFormatter": "xaver.clang-format",
    "editor.formatOnSave": true
},
"[c]": {
    "editor.defaultFormatter": "xaver.clang-format",
    "editor.formatOnSave": true
}
```

#### **📜 Emacs**

1. Install `clang-format` via your package manager
2. Add this to your `.emacs` or `init.el`:

```elisp
(require 'clang-format)
(add-hook 'c++-mode-hook
          (lambda ()
            (add-hook 'before-save-hook 'clang-format-buffer nil 'local)))
(add-hook 'c-mode-hook
          (lambda ()
            (add-hook 'before-save-hook 'clang-format-buffer nil 'local)))
```

To format manually:

```elisp
(global-set-key [C-M-tab] 'clang-format-region)
```

---

## 💡 Notes

- This project **does not support Windows**
- Built with **Qt6** for a modern, cross-platform GUI
- Capable of debugging **multiple binary formats**, not just ELF
- If you’re missing libraries, check your system’s package manager (`apt`, `dnf`, `brew`)
