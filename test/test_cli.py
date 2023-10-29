#!/usr/bin/env python3
# pylint: disable=invalid-name, missing-function-docstring
"""
Integration tests for BookmarkSync
"""
import configparser
import os
import os.path
import shutil
import subprocess
import tempfile
import unittest
import xml.etree.ElementTree as ET

class BookmarkSyncCliIntegrationTest(unittest.TestCase):
    """
    Integration tests for BookmarkSync, using the CLI mode
    """
    TEST_PLACES = [
        ('file:///home', 'Home Sweet Home'),
        ('file:///mnt/externaldrive', 'externaldrive'),
        ('file:///var/www', 'www'),
        ('sftp://example.com/home/james', 'remote server'),
    ]
    TEST_PLACES_FROM_QT = [(pair[0], os.path.basename(pair[0])) for pair in TEST_PLACES[:-1]]
    maxDiff = None

    @classmethod
    def setUpClass(cls):
        os.chdir(os.path.dirname(os.path.abspath(__file__)))
        cls.tmpdir = tempfile.TemporaryDirectory()

    @staticmethod
    def runBookmarkSync(testDir, *args):
        app = os.path.abspath('../src/bookmarksync')
        env = {
            'HOME': testDir,
            # Run the app in headless mode
            'QT_QPA_PLATFORMTHEME': '',
            'QT_QPA_PLATFORM': 'offscreen',
        }
        return subprocess.call([app, *args], cwd=testDir, env=env)

    def makeTestDir(self, testname):
        testDir = os.path.join(self.tmpdir.name, testname)
        os.makedirs(testDir, exist_ok=True)
        return testDir

    def verifyKDE(self, testDir, expectedPlaces):
        filename = os.path.join(testDir, '.local', 'share', 'user-places.xbel')
        xmltree = ET.parse(filename)
        xmlroot = xmltree.getroot()
        self.assertEqual(xmlroot.tag, 'xbel')

        actualPlaces = []
        for child in xmlroot:
            if child.tag == 'bookmark':
                opts = child.attrib
                href = opts['href']
                info = child.find('info')

                ignore = False
                for metadata in info.findall('metadata'):
                    if metadata.find('isSystemItem') is not None:
                        # Ignore built in system entries (Home, Trash, etc.)
                        ignore = True
                        break
                title = child.find('title').text
                if ignore:
                    print('verifyKDE: Ignoring system place', repr(href), repr(title))
                    continue
                actualPlaces.append((href, title))
        self.assertEqual(expectedPlaces, actualPlaces)

    def verifyGTK(self, testDir, expectedPlaces):
        filename = os.path.join(testDir, '.config', 'gtk-3.0', 'bookmarks')
        actualPlaces = []
        with open(filename, encoding='utf-8') as f:
            for line in f:
                line = line.strip()
                try:
                    href, title = line.split(' ', 1)
                except IndexError:
                    href = line
                    title = os.path.basename(href.rstrip('/'))
                actualPlaces.append((href.rstrip('/'), title))
        self.assertEqual(expectedPlaces, actualPlaces)

    def verifyQt(self, testDir, expectedPlaces):
        filename = os.path.join(testDir, '.config', 'QtProject.conf')
        config = configparser.ConfigParser()
        config.read(filename)
        shortcuts = config['FileDialog']['shortcuts']
        # Qt doesn't support custom names or non-local places (i.e. not file://)
        expectedHrefs = [
            pair[0] for pair in expectedPlaces if pair[0].startswith('file://')
        ]
        actualHrefs = shortcuts.split(', ')
        print('verifyQt expected places:', expectedHrefs)
        self.assertEqual(expectedHrefs, actualHrefs)

    def testSyncFromKDE(self):
        testDir = self.makeTestDir('from-kde')
        inputDir = os.path.join(testDir, '.local', 'share')
        os.makedirs(inputDir)
        inputFilename = os.path.join(inputDir, 'user-places.xbel')
        shutil.copy('user-places.xbel.example', inputFilename)
        self.runBookmarkSync(testDir, '-f', 'kde')

        self.verifyGTK(testDir, self.TEST_PLACES)
        self.verifyQt(testDir, self.TEST_PLACES)

    def testSyncFromGTK(self):
        testDir = self.makeTestDir('from-gtk')
        inputDir = os.path.join(testDir, '.config', 'gtk-3.0')
        os.makedirs(inputDir)
        inputFilename = os.path.join(inputDir, 'bookmarks')
        shutil.copy('gtk-bookmarks.example', inputFilename)
        self.runBookmarkSync(testDir, '-f', 'gtk')

        self.verifyKDE(testDir, self.TEST_PLACES)
        self.verifyQt(testDir, self.TEST_PLACES)

    def testSyncFromQt(self):
        testDir = self.makeTestDir('from-qt')
        inputDir = os.path.join(testDir, '.config')
        os.makedirs(inputDir)
        inputFilename = os.path.join(inputDir, 'QtProject.conf')
        shutil.copy('QtProject.conf.example', inputFilename)
        self.runBookmarkSync(testDir, '-f', 'qt')

        print(self.TEST_PLACES_FROM_QT)
        self.verifyKDE(testDir, self.TEST_PLACES_FROM_QT)
        self.verifyGTK(testDir, self.TEST_PLACES_FROM_QT)

if __name__ == '__main__':
    unittest.main()
