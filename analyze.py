import csv
import os
from collections import defaultdict

# --- ler CSV ---
rows = []
with open("resultados.csv", newline="", encoding="utf-16") as f:
    for r in csv.DictReader(f):
        rows.append({
            "depth":        int(r["opt_moves"]),
            "bfs_nodes":    int(r["bfs_nodes"]),
            "astar_nodes":  int(r["astar_nodes"]),
            "bfs_ms":       float(r["bfs_ms"]),
            "astar_ms":     float(r["astar_ms"]),
        })

# --- agregar por profundidade ---
buckets = defaultdict(lambda: {"bfs_nodes": [], "astar_nodes": [], "bfs_ms": [], "astar_ms": []})
for r in rows:
    d = r["depth"]
    buckets[d]["bfs_nodes"].append(r["bfs_nodes"])
    buckets[d]["astar_nodes"].append(r["astar_nodes"])
    buckets[d]["bfs_ms"].append(r["bfs_ms"])
    buckets[d]["astar_ms"].append(r["astar_ms"])

depths     = sorted(buckets)
avg_bfs_n  = [sum(buckets[d]["bfs_nodes"])   / len(buckets[d]["bfs_nodes"])   for d in depths]
avg_ast_n  = [sum(buckets[d]["astar_nodes"])  / len(buckets[d]["astar_nodes"]) for d in depths]
avg_bfs_t  = [sum(buckets[d]["bfs_ms"])       / len(buckets[d]["bfs_ms"])      for d in depths]
avg_ast_t  = [sum(buckets[d]["astar_ms"])     / len(buckets[d]["astar_ms"])    for d in depths]
count      = [len(buckets[d]["bfs_nodes"]) for d in depths]

# --- tabela no terminal ---
print("=" * 72)
print(f"{'Depth':>5} | {'N':>4} | {'BFS nodes':>10} | {'A* nodes':>10} | {'BFS ms':>9} | {'A* ms':>9}")
print("-" * 72)
for i, d in enumerate(depths):
    print(f"{d:>5} | {count[i]:>4} | {avg_bfs_n[i]:>10.0f} | {avg_ast_n[i]:>10.0f} | {avg_bfs_t[i]:>9.1f} | {avg_ast_t[i]:>9.1f}")
print("=" * 72)

total_bfs_n  = sum(r["bfs_nodes"]   for r in rows)
total_ast_n  = sum(r["astar_nodes"] for r in rows)
total_bfs_t  = sum(r["bfs_ms"]      for r in rows)
total_ast_t  = sum(r["astar_ms"]    for r in rows)
print(f"\nTotal nós  — BFS: {total_bfs_n:,}   A*: {total_ast_n:,}   (A* usou {100*total_ast_n/total_bfs_n:.1f}%)")
print(f"Total tempo — BFS: {total_bfs_t/1000:.1f}s   A*: {total_ast_t/1000:.1f}s   (A* usou {100*total_ast_t/total_bfs_t:.1f}%)")

# --- gráficos ---
try:
    import matplotlib.pyplot as plt
    import matplotlib.ticker as mticker
    import numpy as np

    DARK_BG  = "#1a1a2e"
    BFS_COL  = "#e05c5c"   # vermelho
    ASTAR_COL= "#5c9be0"   # azul

    plt.rcParams.update({
        "figure.facecolor":  DARK_BG,
        "axes.facecolor":    "#16213e",
        "axes.edgecolor":    "#555",
        "axes.labelcolor":   "white",
        "xtick.color":       "white",
        "ytick.color":       "white",
        "text.color":        "white",
        "grid.color":        "#333",
        "grid.linestyle":    "--",
        "grid.alpha":        0.5,
        "font.size":         12,
        "legend.facecolor":  "#16213e",
        "legend.edgecolor":  "#555",
    })

    x = np.arange(len(depths))
    w = 0.35

    # ── Gráfico 1: nós expandidos ──────────────────────────────────────────
    fig, ax = plt.subplots(figsize=(11, 5))
    fig.patch.set_facecolor(DARK_BG)
    b1 = ax.bar(x - w/2, avg_bfs_n,  w, label="BFS",  color=BFS_COL,  alpha=0.85)
    b2 = ax.bar(x + w/2, avg_ast_n,  w, label="A*",   color=ASTAR_COL,alpha=0.85)
    ax.set_yscale("log")
    ax.set_xlabel("Profundidade da solução (nº de movimentos)")
    ax.set_ylabel("Nós expandidos (escala log)")
    ax.set_title("Nós Expandidos — BFS vs A*  (média por profundidade)")
    ax.set_xticks(x); ax.set_xticklabels(depths)
    ax.legend(); ax.grid(axis="y")
    for bar in list(b1) + list(b2):
        h = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2, h * 1.15,
                f"{h:.0f}", ha="center", va="bottom", fontsize=8, color="white")
    plt.tight_layout()
    plt.savefig("grafico_nos.png", dpi=150, bbox_inches="tight")
    print("\nGuardado: grafico_nos.png")

    # ── Gráfico 2: tempo ───────────────────────────────────────────────────
    fig, ax = plt.subplots(figsize=(11, 5))
    fig.patch.set_facecolor(DARK_BG)
    b1 = ax.bar(x - w/2, avg_bfs_t,  w, label="BFS",  color=BFS_COL,  alpha=0.85)
    b2 = ax.bar(x + w/2, avg_ast_t,  w, label="A*",   color=ASTAR_COL,alpha=0.85)
    ax.set_yscale("log")
    ax.set_xlabel("Profundidade da solução (nº de movimentos)")
    ax.set_ylabel("Tempo médio (ms, escala log)")
    ax.set_title("Tempo de Execução — BFS vs A*  (média por profundidade)")
    ax.set_xticks(x); ax.set_xticklabels(depths)
    ax.legend(); ax.grid(axis="y")
    for bar in list(b1) + list(b2):
        h = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2, h * 1.15,
                f"{h:.0f}ms", ha="center", va="bottom", fontsize=8, color="white")
    plt.tight_layout()
    plt.savefig("grafico_tempo.png", dpi=150, bbox_inches="tight")
    print("Guardado: grafico_tempo.png")

    # ── Gráfico 3: speedup A* vs BFS ──────────────────────────────────────
    speedup_n = [b/a for b, a in zip(avg_bfs_n, avg_ast_n)]
    speedup_t = [b/a for b, a in zip(avg_bfs_t, avg_ast_t)]
    fig, ax = plt.subplots(figsize=(11, 5))
    fig.patch.set_facecolor(DARK_BG)
    ax.plot(depths, speedup_n, "o-", color=ASTAR_COL, linewidth=2.5,
            markersize=7, label="Redução de nós (BFS/A*)")
    ax.plot(depths, speedup_t, "s--", color="#a0e05c", linewidth=2.5,
            markersize=7, label="Speedup tempo (BFS/A*)")
    ax.axhline(1, color="#888", linewidth=1, linestyle=":")
    ax.set_xlabel("Profundidade da solução")
    ax.set_ylabel("Fator de melhoria (×)")
    ax.set_title("Fator de Melhoria do A* face ao BFS")
    ax.set_xticks(depths); ax.legend(); ax.grid()
    for i, d in enumerate(depths):
        ax.annotate(f"{speedup_n[i]:.1f}×", (d, speedup_n[i]),
                    textcoords="offset points", xytext=(0, 8),
                    ha="center", fontsize=9, color=ASTAR_COL)
    plt.tight_layout()
    plt.savefig("grafico_speedup.png", dpi=150, bbox_inches="tight")
    print("Guardado: grafico_speedup.png")

    plt.show()

except ImportError:
    print("\nmatplotlib não instalado — só a tabela acima foi gerada.")
    print("Para instalar: pip install matplotlib")
