import { Router, Request, Response } from 'express';
import { log, error } from './logger';

const router = Router();

type RippleState = { time: number; amplitude: number; lastAccess: number };

const states = new Map<string, RippleState>();
const ttl = Number(process.env.SESSION_TTL ?? 600000); // 10 minutes

function getState(sessionId: string): RippleState {
  const now = Date.now();
  if (!states.has(sessionId)) {
    states.set(sessionId, { time: 0, amplitude: 1, lastAccess: now });
    log('Created session', sessionId);
  }
  const state = states.get(sessionId)!;
  state.lastAccess = now;
  return state;
}

setInterval(() => {
  const now = Date.now();
  for (const [key, state] of states) {
    if (now - state.lastAccess > ttl) {
      states.delete(key);
      log('Session expired', key);
    }
  }
}, 60_000);

router.get('/state', (req: Request, res: Response) => {
  const session = req.header('X-Session-Id') || 'default';
  const rippleState = getState(session);
  res.json(rippleState);
  log('GET /ripple/state', session, rippleState);
});

router.post('/step', (req: Request, res: Response) => {
  const session = req.header('X-Session-Id') || 'default';
  const rippleState = getState(session);
  const dt = Number(req.body.dt ?? 0.1);
  if (!Number.isFinite(dt) || dt <= 0) {
    error('Invalid dt', dt, 'session', session);
    return res.status(400).json({ error: 'Invalid dt' });
  }
  const freq = Number(process.env.RIPPLE_FREQUENCY ?? 1);
  rippleState.time += dt;
  rippleState.amplitude = Math.cos(rippleState.time * freq);
  res.json(rippleState);
  log('POST /ripple/step', session, dt, rippleState);
});

export default router;
