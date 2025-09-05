// Basic ripple evolution through spacetime
// forward = matter, backward = antimatter

export function propagate(state, dt) {
  const next = { ...state };
  next.time += dt;
  // simple harmonic ripple as placeholder for research-based equation
  next.amplitude = Math.cos(next.time);
  return next;
}
