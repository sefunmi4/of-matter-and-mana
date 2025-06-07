import { Router, Request, Response } from 'express';
import { promises as fs } from 'fs';
import path from 'path';

const router = Router();
const spellbooksDir = path.join(__dirname, '..', 'spellbooks');

router.get('/', async (_req: Request, res: Response) => {
  try {
    const entries = await fs.readdir(spellbooksDir, { withFileTypes: true });
    const books = entries.filter(e => e.isDirectory()).map(e => e.name);
    res.json(books);
  } catch (err) {
    res.status(500).json({ error: 'Failed to list chapters' });
  }
});

router.get('/:book', async (req: Request, res: Response) => {
  const book = req.params.book;
  try {
    const file = path.join(spellbooksDir, book, 'README.md');
    const content = await fs.readFile(file, 'utf-8');
    res.type('text/markdown').send(content);
  } catch (err) {
    res.status(404).json({ error: 'Chapter not found' });
  }
});

export default router;
