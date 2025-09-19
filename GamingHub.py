import tkinter as tk
from tkinter import messagebox
import serial
import time

# ================= Serial Setup =================
try:
    ser = serial.Serial("COM3", 9600, timeout=1)
    time.sleep(2)
except Exception as e:
    ser = None
    print("⚠️ Serial not connected:", e)

# ================= Settings =================
parental_settings = {
    "playtime_limit": 60,
    "allowed_games": {"snake": True, "math": True, "memory": True, "dino": True},
    "save_settings": False
}

# ================= Helper Functions =================
def send_command(char):
    if ser:
        ser.write(char.encode())
        response = ser.readline().decode(errors="ignore").strip()
        if response:
            messagebox.showinfo("STM32 Response", response)
    else:
        messagebox.showerror("Error", "Serial connection not available")

def create_rounded_button(parent, text, command=None, width=220, height=60, radius=20, color="#FF8EC7"):
    canvas = tk.Canvas(parent, width=width, height=height,
                       bg=parent["bg"], highlightthickness=0)
    canvas.pack(pady=10)

    # Draw rounded rectangle
    canvas.create_oval(0, 0, 2*radius, 2*radius, fill=color, outline=color)
    canvas.create_oval(width-2*radius, 0, width, 2*radius, fill=color, outline=color)
    canvas.create_oval(0, height-2*radius, 2*radius, height, fill=color, outline=color)
    canvas.create_oval(width-2*radius, height-2*radius, width, height, fill=color, outline=color)
    canvas.create_rectangle(radius, 0, width-radius, height, fill=color, outline=color)
    canvas.create_rectangle(0, radius, width, height-radius, fill=color, outline=color)

    # Add text
    text_id = canvas.create_text(width//2, height//2,
                                 text=text, font=("Comic Sans MS", 14, "bold"),
                                 fill="white")

    if command:
        def on_click(event):
            command()
        canvas.tag_bind(text_id, "<Button-1>", on_click)
        canvas.bind("<Button-1>", on_click)

    return canvas

# ================= Main GUI =================
def start_main_gui():
    root = tk.Tk()
    root.title("🎮 STM32 Gaming Hub")
    root.geometry("500x550")
    root.config(bg="#93F8E9")

    tk.Label(root, text="🎮 STM32 Gaming Hub ", font=("Comic Sans MS", 22, "bold"),
             bg="#93F8E9", fg="#AD25CF").pack(pady=30)

    if parental_settings["allowed_games"].get("snake", True):
        create_rounded_button(root, "🐍 Play Snake", lambda: send_command('A'))
    if parental_settings["allowed_games"].get("math", True):
        create_rounded_button(root, "XO TicTacToe", lambda: send_command('B'))
    if parental_settings["allowed_games"].get("memory", True):
        create_rounded_button(root, "🧠 Memory Match", lambda: send_command('C'))
        
    if parental_settings["allowed_games"].get("dino", True):
        create_rounded_button(root, "🦖 Dino Run", lambda: send_command('D'))

    root.mainloop()

# ================= Parental Control GUI =================
parental_window = tk.Tk()
parental_window.title("🛡Parental Controls")
parental_window.geometry("500x550")
parental_window.config(bg="#93F8E9")

tk.Label(parental_window, text="🛡Parental Controls", font=("Comic Sans MS", 22, "bold"),
         bg="#93F8E9", fg="#AD25CF").pack(pady=30)

# Frame for settings
frame = tk.Frame(parental_window, bg="#93F8E9")
frame.pack(pady=10, fill="x", padx=50)

# Playtime Limit
tk.Label(frame, text="Playtime Limit (minutes):", font=("Comic Sans MS", 14, "bold"),
         bg="#93F8E9", fg="white").pack(anchor="w", pady=5)
playtime_var = tk.IntVar(value=parental_settings["playtime_limit"])
tk.Entry(frame, textvariable=playtime_var, font=("Comic Sans MS", 12)).pack(pady=5, fill="x")

# Allowed Games - checkboxes
tk.Label(frame, text="Allowed Games:", font=("Comic Sans MS", 14, "bold"),
         bg="#93F8E9", fg="white").pack(anchor="w", pady=10)

game_vars = {}
for game in parental_settings["allowed_games"]:
    var = tk.BooleanVar(value=parental_settings["allowed_games"][game])
    game_vars[game] = var
    cb = tk.Checkbutton(frame, text=game.capitalize(), variable=var,
                        font=("Comic Sans MS", 12), bg="#93F8E9", fg="white",
                        activebackground="#93F8E9", activeforeground="white",
                        selectcolor="#FF8EC7", indicatoron=True)
    cb.pack(anchor="w", pady=3)

# Save Settings checkbox
save_var = tk.BooleanVar(value=parental_settings["save_settings"])
save_cb = tk.Checkbutton(frame, text="Save Settings", variable=save_var,
                         font=("Comic Sans MS", 12), bg="#93F8E9", fg="white",
                         activebackground="#93F8E9", activeforeground="white",
                         selectcolor="#FF8EC7", indicatoron=True)
save_cb.pack(anchor="w", pady=10)

# Continue Button
def save_and_continue():
    parental_settings["playtime_limit"] = playtime_var.get()
    for game in game_vars:
        parental_settings["allowed_games"][game] = game_vars[game].get()
    parental_settings["save_settings"] = save_var.get()

    if not parental_settings["save_settings"]:
        messagebox.showwarning("Parental Control", "You must enable 'Save Settings' to continue.")
        return

    parental_window.destroy()
    start_main_gui()

create_rounded_button(parental_window, "Continue", save_and_continue)

parental_window.mainloop()
# ================= Memory Match Controller GUI =================
def start_memory_gui():
    mem_window = tk.Tk()
    mem_window.title("🧠 Memory Match Controller")
    mem_window.geometry("500x550")
    mem_window.config(bg="#93F8E9")

    tk.Label(mem_window, text="🧠 Memory Match Controller", font=("Comic Sans MS", 22, "bold"),
             bg="#93F8E9", fg="#AD25CF").pack(pady=30)

    # Frame for D-Pad buttons
    frame = tk.Frame(mem_window, bg="#93F8E9")
    frame.pack(pady=20)

    # Up button
    create_rounded_button(frame, "↑ UP", lambda: send_command('X'), width=150, height=60).grid(row=0, column=1, pady=5)

    # Left, Select, Right buttons
    create_rounded_button(frame, "← LEFT", lambda: send_command('L'), width=120, height=60).grid(row=1, column=0, padx=5)
    create_rounded_button(frame, "● SELECT", lambda: send_command('S'), width=120, height=60, color="#4CAF50").grid(row=1, column=1, padx=5)
    create_rounded_button(frame, "→ RIGHT", lambda: send_command('R'), width=120, height=60).grid(row=1, column=2, padx=5)

    # Down button
    create_rounded_button(frame, "↓ DOWN", lambda: send_command('D'), width=150, height=60).grid(row=2, column=1, pady=5)

    mem_window.mainloop()

