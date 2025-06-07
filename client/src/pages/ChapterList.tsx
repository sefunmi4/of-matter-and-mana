import React, { useEffect, useState } from 'react';
import { Link } from 'react-router-dom';

export default function ChapterList() {
  const [chapters, setChapters] = useState<string[]>([]);

  useEffect(() => {
    fetch('/chapters')
      .then((res) => res.json())
      .then(setChapters)
      .catch(() => setChapters([]));
  }, []);

  return (
    <div>
      <h1>Chapters</h1>
      <ul>
        {chapters.map((c) => (
          <li key={c}>
            <Link to={`/chapters/${c}`}>{c}</Link>
          </li>
        ))}
      </ul>
    </div>
  );
}
