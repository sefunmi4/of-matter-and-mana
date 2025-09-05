# Of Matter & Mana

A developer journey told as an interactive spellbook. This repository combines narrative coding, a ripple-based view of spacetime, and research into quantum mechanics.

## Why
Describing hardware (matter) and software (mana) in the language of magic helps build intuition. It also sets the stage for a moral tale about the cost of technology and the choices we make as developers.

## Rules of Spells
1. All magic comes at a cost.
2. Let history be your teacher and books track its lessons.
3. Use stories to understand the dangers before you "cast" a "spell".
4. Ideas are like mana, matter is the medium, and physics is the mechanism.

## Getting Started
Install dependencies and start the development servers:

```bash
npm install
# start the API server (TypeScript via ts-node)
npm run dev
# in a second terminal, start the React client
npm run client
```

The client is built with Vite and React. During development the command above launches it in hot-reload mode.

### Environment variables

Copy `.env.example` to `.env` and adjust values as needed:

```bash
cp .env.example .env
```

`RIPPLE_FREQUENCY` controls the wave frequency. `SESSION_TTL` sets how long a session stays active in milliseconds.

### Building for production

Compile the TypeScript server and build the React client:

```bash
npm run build
```
Start the compiled server:

```bash
npm start
```

To preview the client production build, run:

```bash
npm run preview
```

After logging in at `/login`, navigate to `/spells` to view experimental 3D visualizations of algorithms.

You can also browse the story chapters at `/chapters`.

## Running Tests
Install dev dependencies and run the test suite:

```bash
npm install
npm test
```

The tests cover the ripple engine and chapter routes.


## Repository Layout
- **client/** – React components for the spellbook UI and ripple visualizer.
- **server/** – API endpoints and a simple ripple engine for simulations.
- **game-engine/** – Core physics and time navigation utilities.
- **spellbooks/** – Narrative chapters aligned with the [curriculum](docs/curriculum/README.md).
- **docs/** – Research notes and glossary entries.
- **symbol-cast-algorithms/** – Generalized data structures and algorithms for
  the Symbol Cast runtime in EtherOS. Inputs are visualized as 3D objects and
  complexity is expressed as `O(n) = S(n) + cT(n)` where time is treated as a
  spatial dimension.

The `quantum mechanics` folder contains the ongoing paper *Ripples in Spacetime and Quantum Branches*, which explores a polar coordinate approach to quantum wavefunctions. Source files are under `quantum mechanics/paper`.

## Curriculum
See [docs/curriculum](docs/curriculum/README.md) for a chapter-based roadmap.

## Contributing
This project is experimental. Contributions that expand the spellbooks, improve the ripple engine, or elaborate on the research are welcome.
