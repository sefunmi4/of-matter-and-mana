import request from 'supertest';
import app from '../server/index';

describe('Ripple Engine API', () => {
  beforeEach(() => {
    process.env.RIPPLE_FREQUENCY = '1';
  });

  test('GET /ripple/state returns default state', async () => {
    const res = await request(app).get('/ripple/state');
    expect(res.statusCode).toBe(200);
    expect(res.body).toEqual({ time: 0, amplitude: 1 });
  });

  test('POST /ripple/step advances time', async () => {
    const res = await request(app)
      .post('/ripple/step')
      .send({ dt: 0.5 });
    expect(res.statusCode).toBe(200);
    expect(res.body.time).toBeCloseTo(0.5);
    expect(res.body.amplitude).toBeCloseTo(Math.cos(0.5));
  });
});
