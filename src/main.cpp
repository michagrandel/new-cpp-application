// Provides the application entry point and demonstrates colored UTF-8 console logging.

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <fmt/color.h>

#ifdef _WIN32
#include <windows.h>
#endif

/// <summary>Configures the Windows console for UTF-8 input, output, and ANSI colors.</summary>
/// <remarks>
/// Has no effect on non-Windows platforms. Console configuration is best-effort;
/// failures are not reported, and unavailable output console modes are left unchanged.
/// </remarks>
void setup_terminal_utf8() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    /// <summary>The borrowed standard output handle, which may be null or invalid.</summary>
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Windows consoles require explicit opt-in to interpret ANSI color sequences.
    if (hOut != INVALID_HANDLE_VALUE) {
        /// <summary>The output console mode flags, populated when the console query succeeds.</summary>
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode)) {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, mode);
        }
    }
#endif
}

/// <summary>Initializes console logging and emits sample messages at four severity levels.</summary>
/// <returns>Zero after all sample messages have been emitted successfully.</returns>
/// <remarks>
/// Replaces the process-wide default logger and sets its output pattern and logging
/// threshold. Warning and error messages are demonstration output, not application failures.
/// </remarks>
int main() {
    setup_terminal_utf8();

    /// <summary>The shared color console logger registered as the process-wide default.</summary>
    auto console = spdlog::stdout_color_mt("console");
    spdlog::set_default_logger(console);

    spdlog::set_pattern("[%T] %^[%l]%$ %v");

    spdlog::set_level(spdlog::level::trace);

    spdlog::info("Hello World! Schön dich zu sehen 😊");
    spdlog::warn("Warnung in Gelb mit Smile: 😊");
    spdlog::error("Fehlermeldung in Rot: Alles brennt, aber 😊 bleibt ruhig!");
    spdlog::debug("Debug-Meldung in Cyan/Blau 😊");

    return 0;
}
