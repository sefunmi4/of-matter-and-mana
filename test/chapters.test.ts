import request from 'supertest';
import app from '../server/index';

describe('Chapters API', () => {
  test('GET /chapters returns list', async () => {
    const res = await request(app).get('/chapters');
    expect(res.statusCode).toBe(200);
    expect(Array.isArray(res.body)).toBe(true);
  });

  test('GET /chapters/open-source-development-for-wizards returns markdown', async () => {
    const res = await request(app).get('/chapters/open-source-development-for-wizards');
    expect(res.statusCode).toBe(200);
    expect(res.text).toContain('Open Source Development for Wizards');
  });
});
