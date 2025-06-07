import React from 'react';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';
import Login from './pages/Login';
import Spells from './pages/Spells';
import ChapterList from './pages/ChapterList';
import Chapter from './pages/Chapter';


export default function App() {
  return (
    <Router>
      <Routes>
        <Route path="/login" element={<Login />} />
        <Route path="/spells" element={<Spells />} />
        <Route path="/chapters" element={<ChapterList />} />
        <Route path="/chapters/:book" element={<Chapter />} />
        <Route path="/" element={<Navigate to="/login" replace />} />
      </Routes>
    </Router>
  );
}
